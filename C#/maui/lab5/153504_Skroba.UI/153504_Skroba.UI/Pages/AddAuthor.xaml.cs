using _153504_Skroba.Domain.Entities;
using _153504_Skroba.UI.ViewModels;

namespace _153504_Skroba.UI.Pages;

public partial class AddAuthor : ContentPage
{
	public AddAuthor(AuthorsViewModel authorsViewModel)
	{
		InitializeComponent();

		BindingContext = authorsViewModel;
	}

    public async void OnAddClicked(object sender, EventArgs e)
    {
        Author author = new Author();

        author.Name = this.nameEntry.Text;
        author.Books = new List<Book>();

        await ((AuthorsViewModel)BindingContext).AddAuthorAsync(author);
    }
}