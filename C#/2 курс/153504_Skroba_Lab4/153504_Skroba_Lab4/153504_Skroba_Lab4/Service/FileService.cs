using _153504_Skroba_Lab4.Interface;
using _153504_Skroba_Lab4.Entities;

namespace _153504_Skroba_Lab4.Service
{
    internal class FileService : IFileService<Computer>
    {
        public IEnumerable<Computer> ReadFile(string fileName)
        {
            using (BinaryReader reader = new BinaryReader(File.Open(@fileName, FileMode.Open)))
            {
                while (reader.PeekChar() > -1)
                {
                    yield return new Computer(reader.ReadString(), reader.ReadInt32(), reader.ReadDouble(), reader.ReadBoolean());
                }
            }
        }

        public void SaveData(IEnumerable<Computer> collection, string fileName)
        {
            try
            {
                WritingToFile(collection, fileName);
            }
            catch (IOException)
            {
                File.Delete(fileName);
                WritingToFile(collection, fileName);
            }
        }

        private void WritingToFile(IEnumerable<Computer> collection, string @fileName)
        {
            using (BinaryWriter writer = new BinaryWriter(File.Open(fileName, FileMode.CreateNew)))
            {
                foreach (var item in collection)
                {
                    writer.Write(item.Name);
                    writer.Write(item.ReleaseDate);
                    writer.Write(item.Display);
                    writer.Write(item.TouchID);
                }
            }
        }
    }
}
