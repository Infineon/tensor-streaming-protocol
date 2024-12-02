using System.Text.Json;

namespace DotNetCli;


/// <summary>
/// Provides tools for working with JSON using System.Text.Json.
/// </summary>
internal static class JsonTools
{
    /// <summary>
    /// Selects a token from the JSON document based on the provided JSON path.
    /// </summary>
    /// <param name="json">The root JsonElement.</param>
    /// <param name="jsonPath">The JSON path to select the token.</param>
    /// <returns>The selected token as an object.</returns>
    /// <exception cref="InvalidOperationException">Thrown when the JSON path is invalid.</exception>
    public static object? SelectToken(this JsonElement json, string jsonPath)
    {
        string[] parts = jsonPath.Split(new[] { '.', '[', ']' }, StringSplitOptions.RemoveEmptyEntries);
        JsonElement currentElement = json;

        foreach (var part in parts)
        {
            if (int.TryParse(part, out int index))
            {
                if (currentElement.ValueKind == JsonValueKind.Array)
                {
                    if (index < currentElement.GetArrayLength())
                        currentElement = currentElement[index];
                    else
                        throw new IndexOutOfRangeException($"Array index out of range at path segment '{part}'.");
                }
                else
                {
                    throw new InvalidOperationException($"Expected an array at path segment '{part}', but found '{currentElement.ValueKind}'.");
                }
            }
            else
            {
                if (currentElement.ValueKind == JsonValueKind.Object && currentElement.TryGetProperty(part, out JsonElement property))
                    currentElement = property;
                else
                    throw new InvalidOperationException($"Expected an object at path segment '{part}', but found '{currentElement.ValueKind}' or the property '{part}' does not exist.");
            }
        }

        return currentElement.ValueKind switch
        {
            JsonValueKind.String => currentElement.GetString(),
            JsonValueKind.Number => currentElement.GetDouble(),
            JsonValueKind.True => true,
            JsonValueKind.False => false,
            JsonValueKind.Null => null,
            JsonValueKind.Object => currentElement,
            JsonValueKind.Array => currentElement,
            _ => currentElement.ToString()
        };
    }
}
