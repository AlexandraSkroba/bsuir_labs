using Projects.Entities;
using SQLite;

namespace Projects.Services
{
    public class SQLiteService : IDbService
    {
        private string _dbPath;
        private SQLiteConnection _database;
        public IEnumerable<Artist> GetAllArtists() { 
            return _database.Table<Artist>().ToList();
        }

        public IEnumerable<Song> GetAritistSongs(int artistId)
        {
            return _database.Table<Song>().Where(s => s.ArtistId == artistId).ToList();
        }

        public void Init()
        {
            if (_database != null)
                return;

            _dbPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "Artist_Songs.db");
            _database = new SQLiteConnection(_dbPath);

            _database.DropTable<Artist>();
            _database.DropTable<Song>();
            _database.CreateTable<Artist>();
            _database.CreateTable<Song>();

            // создаем и добавляем объекты Artist
            var artist1 = new Artist { ArtistName = "Bob Marley" };
            var artist2 = new Artist { ArtistName = "Michael Jackson" };
            var artist3 = new Artist { ArtistName = "The Beatles" };
            _database.InsertAll(new[] { artist1, artist2, artist3 });

            // создаем и добавляем объекты Song
            var song1 = new Song { SongName = "No Woman No Cry", ArtistId = artist1.Id };
            var song2 = new Song { SongName = "Song2", ArtistId = artist1.Id };
            var song3 = new Song { SongName = "Thriller", ArtistId = artist2.Id };
            var song4 = new Song { SongName = "Billie Jean", ArtistId = artist2.Id };
            var song5 = new Song { SongName = "Let It Be", ArtistId = artist3.Id };
            var song6 = new Song { SongName = "Imagine", ArtistId = artist3.Id };
            var song7 = new Song { SongName = "Help!", ArtistId = artist3.Id };
            _database.InsertAll(new[] { song1, song2, song3, song4, song5, song6, song7 });
        }
    }
}
