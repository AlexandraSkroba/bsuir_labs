using _153504_Skroba.Application.Abstractions;
using _153504_Skroba.Domain.Entities;
using CommunityToolkit.Mvvm.Input;

namespace _153504_Skroba.UI.ViewModels
{
    public partial class BookDetailsViewModel : IQueryAttributable
    {
        public Book SelectedBook { get; set; }
        private IBookService bookService;
        private AuthorsViewModel authorsViewModel;
        public BookDetailsViewModel(IBookService bookService, AuthorsViewModel authorsViewModel) 
        {
            this.bookService = bookService;
            this.authorsViewModel = authorsViewModel;
        }

        public void ApplyQueryAttributes(IDictionary<string, object> query)
        {
            SelectedBook = (Book) query["Book"]; // System.Collections.Generic.KeyNotFoundException: "The given key 'Book' was not present in the dictionary."
        }

        [RelayCommand]
        public async void EditBook() => await GotoEditWork();
        public async Task GotoEditWork()
        {
            IDictionary<string, object> param = new Dictionary<string, object>()
            {
                { "selectedBook", SelectedBook}
            };

            await Shell.Current.GoToAsync(nameof(EditBook), param); //System.InvalidOperationException: "Unable to resolve service for type '_153504_Skroba.UI.ViewModels.BookEditViewModel' while attempting to activate '_153504_Skroba.UI.Pages.EditBook'."
        }

        [RelayCommand]
        public async void ChangePhoto()
        {
            var result = await FilePicker.Default.PickAsync();

            if (result != null && (result.FileName.EndsWith("png", StringComparison.OrdinalIgnoreCase)
                || result.FileName.EndsWith("jpg", StringComparison.OrdinalIgnoreCase)))
            {
                SelectedBook.ImagePath = result.FileName;

                await authorsViewModel.UpdateBookAsync(SelectedBook);
            }
        }
    }
}
