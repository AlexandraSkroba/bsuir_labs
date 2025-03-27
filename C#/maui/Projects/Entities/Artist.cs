using SQLite;

namespace Projects.Entities
{
    [Table("Artists")]
    public class Artist
    {
        [PrimaryKey, AutoIncrement]

        public int Id { get; set; }
        public string ArtistName { get; set; }
    }
}
