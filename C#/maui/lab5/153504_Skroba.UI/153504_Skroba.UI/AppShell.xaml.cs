using _153504_Skroba.UI.Pages;

namespace _153504_Skroba.UI;

public partial class AppShell : Shell
{
	public AppShell()
	{
		InitializeComponent();

        Routing.RegisterRoute(nameof(BookDetails), typeof(BookDetails));
        Routing.RegisterRoute(nameof(AddAuthor), typeof(AddAuthor));
        Routing.RegisterRoute(nameof(AddBook), typeof(AddBook));
        Routing.RegisterRoute(nameof(Authors), typeof(Authors));
        Routing.RegisterRoute(nameof(EditBook), typeof(EditBook));
    }
}
