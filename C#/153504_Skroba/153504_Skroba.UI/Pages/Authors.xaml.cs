using _153504_Skroba.UI.ViewModels;

namespace _153504_Skroba.UI.Pages;

public partial class Authors : ContentPage
{
	public Authors(AuthorsViewModel authorsViewModel)
	{
		InitializeComponent();
		this.BindingContext = authorsViewModel;
	}
}