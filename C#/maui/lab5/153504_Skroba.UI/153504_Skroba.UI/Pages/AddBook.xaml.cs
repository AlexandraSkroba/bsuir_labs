using _153504_Skroba.Domain.Entities;
using _153504_Skroba.UI.ViewModels;

namespace _153504_Skroba.UI.Pages;

public partial class AddBook : ContentPage
{
	public AddBook(AuthorsViewModel authorsViewModel)
	{
		InitializeComponent();

		BindingContext = authorsViewModel;
	}

    public async void OnAddClicked(object sender, EventArgs e)
    {
        this.alertLabel.Text = "";

        Book book = new Book();

        book.Name = this.nameEntry.Text;
        book.Year = Convert.ToInt32(this.yearEntry.Text);
        book.Rating = Convert.ToInt32(this.ratingEntry.Text);
        book.ImagePath = "blank.png";

        try
        {
            book.AuthorId = ((AuthorsViewModel)BindingContext).Authors.ToList().First(el => el.Name == this.authorEntry.Text).Id;
        }
        catch
        {
            this.alertLabel.Text = "Author not found!";

            return;
        }

        await ((AuthorsViewModel)BindingContext).AddBookAsync(book);
    }
}