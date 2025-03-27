using _153504_Skroba.Application.Abstractions;
using _153504_Skroba.Domain.Entities;


namespace _153504_Skroba.UI.ViewModels
{
    public partial class BookEditViewModel : IQueryAttributable
    {
        public IAuthorService authorService;
        public Book SelectedBook { get; set; }
        public BookEditViewModel(IAuthorService authorService) 
        {
            this.authorService = authorService;
        }

        public void ApplyQueryAttributes(IDictionary<string, object> query)
        {
            SelectedBook = (Book)query["selectedBook"];
        }
    }
}
