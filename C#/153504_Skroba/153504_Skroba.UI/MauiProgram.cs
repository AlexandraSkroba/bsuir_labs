using Microsoft.Extensions.Logging;
using CommunityToolkit.Maui;
using _153504_Skroba.Application.Abstractions;
using _153504_Skroba.Application.Services;
using _153504_Skroba.Domain.Abstractions;
using _153504_Skroba.Persistense.Repository;
using _153504_Skroba.UI.Pages;
using _153504_Skroba.UI.ViewModels;

namespace _153504_Skroba.UI;

public static class MauiProgram
{
	public static MauiApp CreateMauiApp()
	{
		var builder = MauiApp.CreateBuilder();
		builder
			.UseMauiApp<App>()
            .UseMauiCommunityToolkit()
            .ConfigureFonts(fonts =>
			{
				fonts.AddFont("OpenSans-Regular.ttf", "OpenSansRegular");
				fonts.AddFont("OpenSans-Semibold.ttf", "OpenSansSemibold");
			});

#if DEBUG
		builder.Logging.AddDebug();
#endif

        SetupServices(builder.Services);
        return builder.Build();
	}
    private static void SetupServices(IServiceCollection services)
    {
        //Services
        services.AddSingleton<IUnitOfWork, EfUnitOfWork>();
        services.AddSingleton<IAuthorService, AuthorService>();
        services.AddSingleton<IBookService, BookService>();
        //Pages
        services.AddSingleton<Authors>();
        //ViewModels
        services.AddSingleton<AuthorsViewModel>();
    }
}
