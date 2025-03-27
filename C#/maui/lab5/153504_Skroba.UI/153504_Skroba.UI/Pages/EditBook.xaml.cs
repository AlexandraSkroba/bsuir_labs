using _153504_Skroba.UI.ViewModels;

namespace _153504_Skroba.UI.Pages;

public partial class EditBook : ContentPage
{
	AuthorsViewModel authorsViewModel;
	public EditBook(BookEditViewModel bookEditViewModel, AuthorsViewModel authorsViewModel)
	{
		InitializeComponent();

		this.authorsViewModel = authorsViewModel;
		BindingContext = bookEditViewModel;
	}

    public async void OnLoadedPage(object sender, EventArgs e)
    {
        this.nameEntry.Text = ((BookEditViewModel)BindingContext).SelectedBook.Name;
        this.ratingEntry.Text = ((BookEditViewModel)BindingContext).SelectedBook.Rating.ToString();
        this.yearEntry.Text = ((BookEditViewModel)BindingContext).SelectedBook.Year.ToString();
        this.authorEntry.Text = (await ((BookEditViewModel)BindingContext).authorService
            .GetByIdAsync(((BookEditViewModel)BindingContext).SelectedBook.AuthorId)).Name;
    }

    public async void OnUpdateClicked(object sender, EventArgs e)
    {
        this.alertLabel.Text = "";

        ((BookEditViewModel)BindingContext).SelectedBook.Name = this.nameEntry.Text;
        ((BookEditViewModel)BindingContext).SelectedBook.Rating = Convert.ToInt32(this.ratingEntry.Text);
        ((BookEditViewModel)BindingContext).SelectedBook.Year = Convert.ToInt32(this.yearEntry.Text);

        try
        {
            ((BookEditViewModel)BindingContext).SelectedBook.AuthorId = (await ((BookEditViewModel)BindingContext)
                .authorService.GetAllAsync()).Where(el => el.Name == this.authorEntry.Text).First().Id;
        }
        catch
        {
            this.alertLabel.Text = "Author not found";

            return;
        }

        await authorsViewModel.UpdateBookAsync(((BookEditViewModel)BindingContext).SelectedBook);
    }
}