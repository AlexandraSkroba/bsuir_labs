using SQLite;

namespace Projects.Entities
{
    [Table("Songs")]
    public class Song
    {
        [PrimaryKey, AutoIncrement]
        [Column("Id")]
        public int Id { get; set; }
        public string SongName { get; set; }
        [Indexed]
        public int ArtistId { get; set; }
    }
}
