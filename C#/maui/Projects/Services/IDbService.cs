using Projects.Entities;

namespace Projects.Services
{
    public interface IDbService
    {
        IEnumerable<Artist> GetAllArtists();
        IEnumerable<Song> GetAritistSongs(int artistId);
        void Init();
    }
}
