using System.Xml.Linq;
using Google.Protobuf;
using Protocol;

namespace DotNetCli;

internal class XmlSerializerTest
{
    public static Dictionary<string, object?> ProtoMessageToDictionary(IMessage message)
    {
        var fields = message.Descriptor.Fields;
        var dict = new Dictionary<string, object?>();
        foreach (var field in fields.InFieldNumberOrder())
        {
            var value = field.Accessor.GetValue(message);
            dict[field.Name] = value switch
            {
                IMessage subMessage => ProtoMessageToDictionary(subMessage),
                IEnumerable<IMessage> subMessages => subMessages.Select(ProtoMessageToDictionary).ToList(),
                IEnumerable<object> list => list.ToList(),
                _ => value
            };
        }
        return dict;
    }

    public static XElement SerializeToXml(Dictionary<string, object?> dict)
    {
        return new XElement("root", ConvertDictionaryToXElements(dict));
    }

    public static IEnumerable<XElement> ConvertDictionaryToXElements(Dictionary<string, object?> dict)
    {
        foreach (var (key, value) in dict)
        {
            yield return value switch
            {
                Dictionary<string, object?> nestedDict => new XElement(key, ConvertDictionaryToXElements(nestedDict)),
                IEnumerable<object?> list => new XElement(key, list.Select((item, index) =>
                    item switch
                    {
                        Dictionary<string, object?> subDict => new XElement("item", new XAttribute("index", index), ConvertDictionaryToXElements(subDict)),
                        _ => new XElement("item", new XAttribute("index", index), new XAttribute("type", item?.GetType().Name ?? "null"), item)
                    })),
                _ => new XElement(key, new XAttribute("type", value?.GetType().Name ?? "null"), value ?? "")
            };
        }
    }

    public static Dictionary<string, object?> DeserializeFromXml(XElement element)
    {
        return ConvertXElementsToDictionary(element.Elements());
    }

    public static Dictionary<string, object?> ConvertXElementsToDictionary(IEnumerable<XElement> elements)
    {
        var dict = new Dictionary<string, object?>();

        foreach (var element in elements)
        {
            if (element.HasElements)
            {
                bool isList = element.Elements().All(e => e.Name == "item" && e.Attribute("index") != null);
                if (isList)
                {
                    var list = element.Elements().Select(itemElement =>
                        itemElement.HasElements
                            ? ConvertXElementsToDictionary(itemElement.Elements())
                            : ConvertValueFromType(itemElement)).ToList();
                    dict[element.Name.LocalName] = list;
                }
                else
                {
                    dict[element.Name.LocalName] = ConvertXElementsToDictionary(element.Elements());
                }
            }
            else
            {
                dict[element.Name.LocalName] = ConvertValueFromType(element);
            }
        }

        return dict;
    }

    private static object? ConvertValueFromType(XElement element)
    {
        var typeAttr = element.Attribute("type");
        if (typeAttr != null)
        {
            var value = element.Value;
            return typeAttr.Value switch
            {
                "null" => null,
                "DeviceType" => Enum.Parse<DeviceType>(value),
                "DeviceStatus" => Enum.Parse<DeviceStatus>(value),
                "StreamDirection" => Enum.Parse<StreamDirection>(value),
                "DataType" => Enum.Parse<DataType>(value),
                "Boolean" => Boolean.Parse(value),
                "Int32" => Int32.Parse(value),
                "UInt32" => UInt32.Parse(value),
                "Single" => Single.Parse(value),
                "String" => value,
                null => null,
                _ => throw new Exception("Unknown type"),
                // _ => Convert.ChangeType(element.Value, Type.GetType("System." + typeAttr.Value)),
            } ;

        }

        return element.Value;
    }

    public static void FooBar(Response response)
    {
        var dict1 = XmlSerializerTest.ProtoMessageToDictionary(response);
        var xml1 = XmlSerializerTest.SerializeToXml(dict1);
        var dict2 = XmlSerializerTest.DeserializeFromXml(xml1);
        var xml2 = XmlSerializerTest.SerializeToXml(dict2);

        Console.WriteLine(xml1.ToString());
        Console.WriteLine("----");

        Console.WriteLine(xml2.ToString());

        Console.WriteLine("----");

        Console.WriteLine(xml1.ToString() == xml2.ToString());

        //Console.WriteLine(XmlSerializerTest.SerializeToXml(dict));

        //var xml = XmlSerializerTest.ConvertXElementsToDictionary(XmlSerializerTest.ConvertDictionaryToXElements(dict));

        /*
        foreach (var kvp in xml)
        {
            Console.WriteLine(kvp.Key);
            Console.WriteLine(kvp.Value);
        } */

    }
}
