using _153504_Skroba.UI.ViewModels;

namespace _153504_Skroba.UI.Pages;

public partial class BookDetails : ContentPage
{
	public BookDetails(BookDetailsViewModel bookDetailsViewModel)
	{
		InitializeComponent();
		this.BindingContext= bookDetailsViewModel;
	}

	public void OnLoadPage(object sender, EventArgs e)
	{
		this.yearLabe.Text = "Год издания: " + ((BookDetailsViewModel)BindingContext).SelectedBook.Year;
        this.nameLabel.Text = "Название: " + ((BookDetailsViewModel)BindingContext).SelectedBook.Name;
        this.ratingLabel.Text = "Рэйтинг: " + ((BookDetailsViewModel)BindingContext).SelectedBook.Rating;
		this.photo.Source = ((BookDetailsViewModel)BindingContext).SelectedBook.ImagePath;
    }
}