using System.Globalization;
using System.Runtime.InteropServices;
using System.Text;
using Protocol;

namespace DotNetCli;

public class CsvWriter : IStreamHandler
{
    private readonly string? _filePath;
    private TextWriter? _writer;
    private int _framesLeft;
    private DataType _elementType;
    private int _elementCount;   // shape.flat, number of elements in one frame
    private int _elementSize;

    public CsvWriter(string? targetPath = null, int frameCount = 1)
    {
        if (String.IsNullOrWhiteSpace(_filePath))
            _filePath = null;

        _filePath = targetPath;
        _framesLeft = frameCount;
    }

    private double[] ConvertFromBytes(DataType type, ReadOnlySpan<byte> bytes)
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

    public void Start(StreamConfig stream)
    {
        if (_writer != null)
        {
            Console.WriteLine("Write already in progress. Restarting...");
            Close();
        }

        _elementCount = 1;
        foreach (var d in stream.Shape)
        {
            _elementCount *= d.Size;
        }

        if(_filePath == null) 
        {
            Console.WriteLine($"Starts writing to Console, {_elementCount} columns.");
            _writer = Console.Out;
        }
        else
        {
            Console.WriteLine($"Starts writing to {_filePath}, {_elementCount} columns.");
            var fileStream = new FileStream(_filePath, FileMode.OpenOrCreate);
            fileStream.SetLength(0);
            _writer = new StreamWriter(fileStream, Encoding.UTF8);
        }

        _elementType = stream.Datatype;

        _elementSize = _elementType switch
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

    public bool ProcessDataChunk(DataChunk data)
    {
        if (_writer == null)
            return false;

        if (_framesLeft > 0)
        {
            int expectedTotal = data.FrameCount * _elementSize * _elementCount;
            if (data.Payload.Span.Length != expectedTotal)
            {
                Console.WriteLine($"Unexpected payload size of {data.Payload.Span.Length} bytes. Expected {expectedTotal} bytes.");
                Close();
                return false;
            }

            var converted = ConvertFromBytes(_elementType, data.Payload.Span);
            for (int i = 0; i < data.FrameCount && _framesLeft > 0; i++)
            {
                WriteLine(converted.AsSpan(i * _elementCount, _elementCount));
                _framesLeft -= _elementCount;
            }
        }

        if (_framesLeft != 0) 
            return true;
        
        Close();
        return false;
    }

    private void Close()
    {
        if (_writer != null)
        {
            Console.WriteLine($"Closed {_filePath ?? "Output"}.");
            _writer.Flush();
            if (_writer != Console.Out)
            {
                _writer.Close();
                _writer.Dispose();
            }
            _writer = null;
        }
    }

    private void WriteLine(Span<double> frame)
    {
        
        if(_writer == null)
            return;

        for (var index = 0; index < frame.Length; index++)
        {
            var value = frame[index];
            _writer.Write(value.ToString(CultureInfo.InvariantCulture));
            if(index != frame.Length - 1)
                _writer.Write(", ");
        }
        _writer.WriteLine();
    }
}