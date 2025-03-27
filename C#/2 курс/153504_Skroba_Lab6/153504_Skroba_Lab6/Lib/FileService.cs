using System.Text.Json;
using _153504_Skroba_Lab6;

namespace Lib
{
    public class FileService<T> : IFileService<T> where T : class
    {
        public IEnumerable<T> ReadFile(string fileName)
        {
            using (FileStream fileStream = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                return JsonSerializer.Deserialize(fileStream, typeof(List<T>)) as List<T>;
            }
        }

        public void SaveData(IEnumerable<T> data, string fileName)
        {
            using (FileStream fileStream = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                JsonSerializer.Serialize(fileStream, data);
            }
        }

    }
}