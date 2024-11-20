using Protocol;
using System.Globalization;
using System.Text;
using Google.Protobuf.Collections;

namespace DotNetCli;

internal static class ResponseStringFormat
{
    public static string Format(this DeviceConfigurationResponse response)
    {
        var ret = new StringBuilder();
        int indent = 0;
        void Line(string key, object? value = null) => ret.AppendLine((new String(' ', indent) + key).PadRight(30) + value);

        Line("-------------- Device Configuration --------------");
        Line($"[Device {response.Device}]");
        indent += 4;
        Line("Status", response.Status);
        foreach (var option in response.Options)
        {
            Line($"[Option {option.OptionId}]");
            indent += 4;
            switch (option.ValueCase)
            {
                case OptionValue.ValueOneofCase.None:
                    Line("Type", "Invalid");
                    Line("Value", "");
                    break;
                case OptionValue.ValueOneofCase.IntValue:
                    Line("Type", "Integer");
                    Line("Value", option.IntValue);
                    break;
                case OptionValue.ValueOneofCase.FloatValue:
                    Line("Type", "Float");
                    Line("Value", option.FloatValue.ToString(CultureInfo.InvariantCulture));
                    break;
                case OptionValue.ValueOneofCase.BoolValue:
                    Line("Type", "Boolean");
                    Line("Value", option.BoolValue);
                    break;
                case OptionValue.ValueOneofCase.OneofValue:
                    Line("Type", "OneOf");
                    Line("Value", option.OneofValue);
                    break;
                default:
                    throw new ArgumentOutOfRangeException();
            }
            indent -= 4;
        }
        
        ret.Append(response.Streams.Format(indent));

        indent -= 4;
        return ret.ToString();
    }

    public static string Format(this RepeatedField<StreamConfig> streams, int indent = 0)
    {
        var ret = new StringBuilder();
        void Line(string key, object? value = null) => ret.AppendLine((new String(' ', indent) + key).PadRight(30) + value);

        int id = 0;
        foreach (var stream in streams)
        {
            Line($"[Stream {id++}]");
            indent += 4;
            Line("Current Frame", stream.CurrentFrame);
            Line("Frames Dropped", stream.FramesDropped);
            Line("Name", stream.Name);
            Line("Direction", stream.Direction);
            Line("Frequency", stream.Frequency + " Hz");
            Line("Type", stream.Datatype);
            Line("Scale", stream.Scale);
            Line("Offset", stream.Offset);
            Line("Unit", stream.Unit);
            Line("Shape", string.Join(",", stream.Shape.Select(x => x.Size)));
            Line("Dimension Names", string.Join(",", stream.Shape.Select(x => x.Name)));
            Line("Shape Labels", string.Join(",", stream.Shape.Select(x => "{" + string.Join(",", x.Labels) + "}")));
            Line("Max Frame Count", stream.MaxFrameCount);
            indent -= 4;
        }
        return ret.ToString();
    }

    public static string Format(this ErrorResponse error)
    {
        return $"Error (Code {error.ErrorCode}): {error.ErrorMessage}";
    }


    public static string Format(this Protocol.Version version)
    {
        return $"{version.Major}.{version.Minor}.{version.Build}.{version.Revision}";
    }

    public static string Format(this BoardCapabilitiesResponse response)
    {
        var ret = new StringBuilder();
        int indent = 0;
        void Line(string key, object? value = null) => ret.AppendLine((new String(' ', indent) + key).PadRight(30) + value);

        Line("-------------- Board Capabilities --------------");
        Line("Board Name", response.Board.Name);
        Line("Serial", new Guid(response.Board.Serial.Uuid.Span, bigEndian: true));
        Line("Firmware Version", response.Board.FirmwareVersion.Format());
        Line("Protocol Version", response.Board.ProtocolVersion.Format());
        Line("Watchdog Timeout", response.Board.WatchdogTimeout + " msec");
        foreach (var device in response.Board.Devices)
        {
            Line($"[Device {device.DeviceId}]");
            indent += 4;
            Line("Name", device.Name);
            if (!String.IsNullOrEmpty(device.Description))
                Line("Description", device.Description);
            Line("Status", device.Status);
            if(!String.IsNullOrEmpty(device.StatusMessage))
                Line("Status Message", device.StatusMessage);
            foreach (var option in device.Options)
            {
                Line($"[Option {option.OptionId}]");
                indent += 4;
                Line("Name", option.Name);
                if (!String.IsNullOrEmpty(option.Description))
                    Line("Description", option.Description);
                switch (option.ValueCase)
                {
                    case Option.ValueOneofCase.FloatType:
                        Line("Type", "Float");
                        Line("Value", option.FloatType.CurrentValue.ToString(CultureInfo.InvariantCulture));
                        Line("Default", option.FloatType.DefaultValue);
                        Line("Min", option.FloatType.MinValue);
                        Line("Max", option.FloatType.MaxValue);
                        break;
                    case Option.ValueOneofCase.IntType:
                        Line("Type", "Integer");
                        Line("Value", option.IntType.CurrentValue);
                        Line("Default", option.IntType.DefaultValue);
                        Line("Min", option.IntType.MinValue);
                        Line("Max", option.IntType.MaxValue);
                        break;
                    case Option.ValueOneofCase.BoolType:
                        Line("Type", "Boolean");
                        Line("Value", option.BoolType.CurrentValue);
                        Line("Default", option.BoolType.DefaultValue);
                        break;
                    case Option.ValueOneofCase.OneofType:
                        Line("Type", "OneOf");
                        Line("Value", option.OneofType.CurrentIndex);
                        Line("Default", option.OneofType.DefaultIndex);
                        Line("One of Items", String.Join(", ", option.OneofType.Items));
                        break;
                }
                indent -= 4;
            }
           
            ret.Append(device.Streams.Format(indent));
            indent -= 4;
        }

        return ret.ToString();
    }
}
