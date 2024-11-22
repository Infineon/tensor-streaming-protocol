/*
 * Credits to https://github.com/mathnet/mathnet-numerics
 */


using System.ComponentModel;

namespace DotNetCli;

public class RunningStatistics : IEquatable<RunningStatistics>
{
    public long _n;

    public double _min = double.PositiveInfinity;

    public double _max = double.NegativeInfinity;

    public double _m1;

    public double _m2;

    public double _m3;

    public double _m4;

    /// <summary>
    /// Gets the total number of samples.
    /// </summary>
    [DisplayName("Count")]
    public long Count => _n;

    /// <summary>
    /// Returns the minimum value in the sample data.
    /// Returns NaN if data is empty or if any entry is NaN.
    /// </summary>
    [DisplayName("Minimum")]
    [Description("The minimum value in the sample data.")]
    public double Minimum => _n > 0 ? _min : double.NaN;

    /// <summary>
    /// Returns the maximum value in the sample data.
    /// Returns NaN if data is empty or if any entry is NaN.
    /// </summary>
    [DisplayName("Maximum")]
    [Description("The maximum value in the sample data.")]
    public double Maximum => _n > 0 ? _max : double.NaN;

    /// <summary>
    /// Evaluates the sample mean, an estimate of the population mean.
    /// Returns NaN if data is empty or if any entry is NaN.
    /// </summary>
    [DisplayName("Mean")]
    [Description("An estimate of the population mean.")]
    public double Mean => _n > 0 ? _m1 : double.NaN;

    /// <summary>
    /// Estimates the unbiased population variance from the provided samples.
    /// On a dataset of size N will use an N-1 normalizer (Bessel's correction).
    /// Returns NaN if data has less than two entries or if any entry is NaN.
    /// </summary>
    [DisplayName("Variance")]
    [Description("Estimates the unbiased population variance from the provided samples.\nOn a dataset of size N will use an N-1 normalizer (Bessel's correction).")]
    public double Variance => _n < 2 ? double.NaN : _m2 / (_n - 1);

    /// <summary>
    /// Evaluates the variance from the provided full population.
    /// On a dataset of size N will use an N normalizer and would thus be biased if applied to a subset.
    /// Returns NaN if data is empty or if any entry is NaN.
    /// </summary>
    [DisplayName("Population Variance")]
    [Description("The variance from the provided full population.\nOn a dataset of size N will use an N normalizer and would thus be biased if applied to a subset.")]
    public double PopulationVariance => _n < 2 ? double.NaN : _m2 / _n;

    /// <summary>
    /// Estimates the unbiased population standard deviation from the provided samples.
    /// On a dataset of size N will use an N-1 normalizer (Bessel's correction).
    /// Returns NaN if data has less than two entries or if any entry is NaN.
    /// </summary>
    [DisplayName("Standard Deviation")]
    [Description("The unbiased population standard deviation from the provided samples.\nOn a dataset of size N will use an N-1 normalizer (Bessel's correction).")]
    public double StandardDeviation => _n < 2 ? double.NaN : Math.Sqrt(_m2 / (_n - 1));

    /// <summary>
    /// Evaluates the standard deviation from the provided full population.
    /// On a dataset of size N will use an N normalizer and would thus be biased if applied to a subset.
    /// Returns NaN if data is empty or if any entry is NaN.
    /// </summary>
    [DisplayName("Population Standard Deviation")]
    [Description("The standard deviation from the provided full population.\nOn a dataset of size N will use an N normalizer and would thus be biased if applied to a subset.")]
    public double PopulationStandardDeviation => _n < 2 ? double.NaN : Math.Sqrt(_m2 / _n);

    /// <summary>
    /// Estimates the unbiased population skewness from the provided samples.
    /// Uses a normalizer (Bessel's correction; type 2).
    /// Returns NaN if data has less than three entries or if any entry is NaN.
    /// </summary>
    [DisplayName("Skewness")]
    [Description("The unbiased population skewness from the provided samples.\nUses a normalizer (Bessel's correction; type 2).")]
    public double Skewness => _n < 3 ? double.NaN : (_n * _m3 * Math.Sqrt(_m2 / (_n - 1)) / (_m2 * _m2 * (_n - 2))) * (_n - 1);

    /// <summary>
    /// Evaluates the population skewness from the full population.
    /// Does not use a normalizer and would thus be biased if applied to a subset (type 1).
    /// Returns NaN if data has less than two entries or if any entry is NaN.
    /// </summary>
    [DisplayName("Population Skewness")]
    [Description("The population skewness from the full population.\nDoes not use a normalizer and would thus be biased if applied to a subset (type 1).")]
    public double PopulationSkewness => _n < 2 ? double.NaN : Math.Sqrt(_n) * _m3 / Math.Pow(_m2, 1.5);

    /// <summary>
    /// Estimates the unbiased population excess kurtosis from the provided samples.
    /// Uses a normalizer (Bessel's correction; type 2).
    /// Returns NaN if data has less than four entries or if any entry is NaN.
    /// </summary>
    [DisplayName("Kurtosis")]
    [Description("The unbiased population excess kurtosis from the provided samples.\nUses a normalizer (Bessel's correction; type 2).")]
    public double Kurtosis => _n < 4 ? double.NaN : ((double)_n * _n - 1) / ((_n - 2) * (_n - 3)) * (_n * _m4 / (_m2 * _m2) - 3 + 6.0 / (_n + 1));

    /// <summary>
    /// Evaluates the population excess kurtosis from the full population.
    /// Does not use a normalizer and would thus be biased if applied to a subset (type 1).
    /// Returns NaN if data has less than three entries or if any entry is NaN.
    /// </summary>
    [DisplayName("Population Kurtosis")]
    [Description("The population excess kurtosis from the full population.\nDoes not use a normalizer and would thus be biased if applied to a subset (type 1).")]
    public double PopulationKurtosis => _n < 3 ? double.NaN : _n * _m4 / (_m2 * _m2) - 3.0;


    public RunningStatistics()
    {
    }

    public RunningStatistics(IEnumerable<double> values)
    {
        PushRange(values);
    }

    public RunningStatistics(long n, double min, double max, double m1, double m2, double m3, double m4)
    {
        _n = n;
        _min = min;
        _max = max;
        _m1 = m1;
        _m2 = m2;
        _m3 = m3;
        _m4 = m4;
    }

    public void Reset()
    {
        _n = 0;
        _min = 0;
        _max = 0;
        _m1 = 0;
        _m2 = 0;
        _m3 = 0;
        _m4 = 0;
    }

    /// <summary>
    /// Update the running statistics by adding another observed sample (in-place).
    /// </summary>
    public void Push(double value)
    {
        _n++;
        double d = value - _m1;
        double s = d / _n;
        double s2 = s * s;
        double t = d * s * (_n - 1);

        _m1 += s;
        _m4 += t * s2 * (_n * _n - 3 * _n + 3) + 6 * s2 * _m2 - 4 * s * _m3;
        _m3 += t * s * (_n - 2) - 3 * s * _m2;
        _m2 += t;

        if (value < _min || double.IsNaN(value))
        {
            _min = value;
        }

        if (value > _max || double.IsNaN(value))
        {
            _max = value;
        }
    }

    /// <summary>
    /// Update the running statistics by adding a sequence of observed sample (in-place).
    /// </summary>
    public void PushRange(IEnumerable<double> values)
    {
        foreach (double value in values)
        {
            Push(value);
        }
    }


    /// <summary>
    /// Update the running statistics by adding a sequence of observed sample (in-place).
    /// </summary>
    public void PushRange(IEnumerable<float> values)
    {
        foreach (float value in values)
        {
            Push(value);
        }
    }

    public void Push(RunningStatistics other)
    {
        var result = Combine(this, other);
        _n = result._n;
        _min = result._min;
        _max = result._max;
        _m1 = result._m1;
        _m2 = result._m2;
        _m3 = result._m3;
        _m4 = result._m4;
    }

    /// <summary>
    /// Create a new running statistics over the combined samples of two existing running statistics.
    /// </summary>
    public static RunningStatistics Combine(RunningStatistics a, RunningStatistics b)
    {
        if (a._n == 0)
        {
            return b;
        }
        else if (b._n == 0)
        {
            return a;
        }

        long n = a._n + b._n;
        double d = b._m1 - a._m1;
        double d2 = d * d;
        double d3 = d2 * d;
        double d4 = d2 * d2;

        double m1 = (a._n * a._m1 + b._n * b._m1) / n;
        double m2 = a._m2 + b._m2 + d2 * a._n * b._n / n;
        double m3 = a._m3 + b._m3 + d3 * a._n * b._n * (a._n - b._n) / (n * n)
                    + 3 * d * (a._n * b._m2 - b._n * a._m2) / n;
        double m4 = a._m4 + b._m4 + d4 * a._n * b._n * (a._n * a._n - a._n * b._n + b._n * b._n) / (n * n * n)
                    + 6 * d2 * (a._n * a._n * b._m2 + b._n * b._n * a._m2) / (n * n) + 4 * d * (a._n * b._m3 - b._n * a._m3) / n;

        double min = Math.Min(a._min, b._min);
        double max = Math.Max(a._max, b._max);

        return new RunningStatistics { _n = n, _m1 = m1, _m2 = m2, _m3 = m3, _m4 = m4, _min = min, _max = max };
    }

    public static RunningStatistics operator +(RunningStatistics a, RunningStatistics b)
    {
        return Combine(a, b);
    }

    public static bool operator ==(RunningStatistics a, RunningStatistics b)
    {
        if (ReferenceEquals(null, a))
            return false;

        return a.Equals(b);
    }

    public static bool operator !=(RunningStatistics a, RunningStatistics b)
    {
        return !(a == b);
    }

    /// <summary>Indicates whether the current object is equal to another object of the same type.</summary>
    /// <param name="other">An object to compare with this object.</param>
    /// <returns>
    /// <see langword="true" /> if the current object is equal to the <paramref name="other" /> parameter; otherwise, <see langword="false" />.</returns>
    public bool Equals(RunningStatistics other)
    {
        if (ReferenceEquals(null, other)) return false;
        if (ReferenceEquals(this, other)) return true;
        return _n == other._n && _min.Equals(other._min) && _max.Equals(other._max) && _m1.Equals(other._m1) && _m2.Equals(other._m2) && _m3.Equals(other._m3) && _m4.Equals(other._m4);
    }

    /// <summary>Determines whether the specified object is equal to the current object.</summary>
    /// <param name="obj">The object to compare with the current object.</param>
    /// <returns>
    /// <see langword="true" /> if the specified object  is equal to the current object; otherwise, <see langword="false" />.</returns>
    public override bool Equals(object obj)
    {
        if (ReferenceEquals(null, obj)) return false;
        if (ReferenceEquals(this, obj)) return true;
        if (obj.GetType() != this.GetType()) return false;
        return Equals((RunningStatistics)obj);
    }

    /// <summary>Serves as the default hash function.</summary>
    /// <returns>A hash code for the current object.</returns>
    public override int GetHashCode()
    {
        return HashCode.Combine(_n, _min, _max, _m1, _m2, _m3, _m4);
    }

    /// <summary>Returns a string that represents the current object.</summary>
    /// <returns>A string that represents the current object.</returns>
    public override string ToString()
    {
        return $"Count={Count}, Minimum={Minimum}, Maximum={Maximum}, Mean={Mean}, Variance={Variance}";
    }
}