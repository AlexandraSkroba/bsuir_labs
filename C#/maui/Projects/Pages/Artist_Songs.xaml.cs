using Projects.Entities;
using Projects.Services;
namespace Projects.Pages;

public partial class Artist_Songs : ContentPage
{
    private IDbService _dbService;
    public Artist_Songs(IDbService dbService)
	{
		InitializeComponent();
        _dbService = dbService;
    }

    private void OnPickerSelectedIndexChanged(object sender, EventArgs e)
    {
        var picker = sender as Picker;
        int selectedIndex = picker.SelectedIndex;

        ServicesView.ItemsSource = _dbService.GetAritistSongs(selectedIndex + 1).
            Select(d => d.SongName).ToList();
    }

    private void OnPageLoad(object sender, EventArgs e)
    {
        _dbService.Init();
        Picker.ItemsSource = _dbService.GetAllArtists().Select(r => r.ArtistName).ToList();
        Picker.ItemsSource = Picker.GetItemsAsArray();
    }
}