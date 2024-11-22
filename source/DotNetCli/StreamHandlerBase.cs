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
            throw new InvalidDataException("Stream already in progress. ");
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

    public abstract bool ProcessDataChunk(DataChunk data);

    protected double[] ToDoubles(DataType type, ReadOnlySpan<byte> bytes)
    {
        double[] result;

        switch (type)
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
            case DataType.Unknown:
                result = new double[0];
                break;
            default:
                throw new ArgumentOutOfRangeException(nameof(type), type, null);
        }

        return result;
    }
}