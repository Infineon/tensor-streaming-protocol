using System.Runtime.InteropServices;
using Protocol;

namespace DotNetCli;

public abstract class StreamHandlerBase : IStreamHandler
{
    protected DataType ElementType { get; private set; }
    protected int ElementCount { get; private set; }   // shape.flat, number of elements in one frame
    protected int ElementSize { get; private set; }
    protected StreamConfig? Stream { get; private set; }
    protected IClient Client { get; private set; }

    public StreamHandlerBase(IClient client)
    {
        Client = client;
    }

    public virtual void Start(StreamConfig stream)
    {
        if (Stream != null)
            return;

        Stream = stream;

        ElementCount = 1;
        foreach (var d in stream.Shape)
        {
            ElementCount *= d.Size;
        }

        ElementType = stream.Datatype;

        ElementSize = ElementType switch
        {
            DataType.Unknown => 0,
            DataType.U8 => 1,
            DataType.S8 => 1,
            DataType.U16 => 2,
            DataType.S16 => 2,
            DataType.U32 => 4,
            DataType.S32 => 4,
            DataType.F32 => 4,
            DataType.F64 => 8,
            _ => throw new ArgumentOutOfRangeException()
        };
    }

    public virtual bool ProcessDataChunk(DataChunk data) => true;

    public virtual bool ProcessDataInquire(DataInquire data) => true;

    protected byte[] NormalizedToBytesSaturating(double[] normalized)
    {
        var result = new List<byte>(ElementCount * ElementSize);
        switch (ElementType)
        {
            case DataType.U8:
                foreach (var value in normalized)
                {
                    var sat = byte.CreateSaturating(value * byte.MaxValue);
                    result.Add(sat);
                }
                break;
            case DataType.S8:
                foreach (var value in normalized)
                {
                    var sat = sbyte.CreateSaturating(value * sbyte.MaxValue);
                    result.Add(unchecked((byte)sat));
                }
                break;
            case DataType.U16:
                foreach (var value in normalized)
                {
                    var sat = ushort.CreateSaturating(value * ushort.MaxValue);
                    result.AddRange(BitConverter.GetBytes(sat));
                }
                break;
            case DataType.S16:
                foreach (var value in normalized)
                {
                    var sat = short.CreateSaturating(value * short.MaxValue);
                    result.AddRange(BitConverter.GetBytes(sat));
                }
                break;
            case DataType.U32:
                foreach (var value in normalized)
                {
                    var sat = uint.CreateSaturating(value * uint.MaxValue);
                    result.AddRange(BitConverter.GetBytes(sat));
                }
                break;
            case DataType.S32:
                foreach (var value in normalized)
                {
                    var sat = int.CreateSaturating(value * int.MaxValue);
                    result.AddRange(BitConverter.GetBytes(sat));
                }
                break;
            case DataType.F32:
                foreach (var value in normalized)
                {
                    result.AddRange(BitConverter.GetBytes((float)value));
                }
                break;
            case DataType.F64:
                foreach (var value in normalized)
                {
                    result.AddRange(BitConverter.GetBytes((double)value));
                }
                break;
            case DataType.Q7:
            case DataType.Q15:
            case DataType.Q31:
                throw new NotImplementedException("Not yet implemented.");
            case DataType.D8:
            case DataType.D16:
            case DataType.D32:
                throw new NotImplementedException("Not yet implemented.");
            case DataType.Unknown:
                throw new NotSupportedException();
           
            default:
                throw new ArgumentOutOfRangeException(nameof(ElementType), ElementType, null);
        }

        return result.ToArray();
    }


    protected double[] ToDoubles(ReadOnlySpan<byte> bytes)
    {
        double[] result;

        switch (ElementType)
        {
            case DataType.U8:
                result = new double[bytes.Length];
                for (int i = 0; i < bytes.Length; i++) result[i] = bytes[i];
                break;
            case DataType.S8:
                var s8Span = MemoryMarshal.Cast<byte, sbyte>(bytes);
                result = new double[s8Span.Length];
                for (int i = 0; i < s8Span.Length; i++) result[i] = s8Span[i];
                break;
            case DataType.U16:
                var u16Span = MemoryMarshal.Cast<byte, ushort>(bytes);
                result = new double[u16Span.Length];
                for (int i = 0; i < u16Span.Length; i++) result[i] = u16Span[i];
                break;
            case DataType.S16:
                var s16Span = MemoryMarshal.Cast<byte, short>(bytes);
                result = new double[s16Span.Length];
                for (int i = 0; i < s16Span.Length; i++) result[i] = s16Span[i];
                break;
            case DataType.U32:
                var u32Span = MemoryMarshal.Cast<byte, uint>(bytes);
                result = new double[u32Span.Length];
                for (int i = 0; i < u32Span.Length; i++) result[i] = u32Span[i];
                break;
            case DataType.S32:
                var s32Span = MemoryMarshal.Cast<byte, int>(bytes);
                result = new double[s32Span.Length];
                for (int i = 0; i < s32Span.Length; i++) result[i] = s32Span[i];
                break;
            case DataType.F32:
                var f32Span = MemoryMarshal.Cast<byte, float>(bytes);
                result = new double[f32Span.Length];
                for (int i = 0; i < f32Span.Length; i++) result[i] = f32Span[i];
                break;
            case DataType.F64:
                var f64Span = MemoryMarshal.Cast<byte, double>(bytes);
                result = new double[f64Span.Length];
                for (int i = 0; i < f64Span.Length; i++) result[i] = f64Span[i];
                break;
            case DataType.Q7:
            case DataType.Q15:
            case DataType.Q31:
                throw new NotImplementedException("Not yet implemented.");
            case DataType.D8:
            case DataType.D16:
            case DataType.D32:
                throw new NotImplementedException("Not yet implemented.");
            case DataType.Unknown:
                result = new double[0];
                break;
            default:
                throw new ArgumentOutOfRangeException(nameof(ElementType), ElementType, null);
        }

        return result;
    }
}