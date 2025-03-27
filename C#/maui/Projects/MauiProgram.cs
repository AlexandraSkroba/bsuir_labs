using Projects.Pages;
using Projects.Services;
namespace Projects;

public static class MauiProgram
{
	public static MauiApp CreateMauiApp()
	{
		var builder = MauiApp.CreateBuilder();
		builder
			.UseMauiApp<App>()
			.ConfigureFonts(fonts =>
			{
				fonts.AddFont("OpenSans-Regular.ttf", "OpenSansRegular");
				fonts.AddFont("OpenSans-Semibold.ttf", "OpenSansSemibold");
			});

		builder.Services.AddSingleton<Artist_Songs>();
		builder.Services.AddTransient<IDbService, SQLiteService>();


        builder.Services.AddHttpClient<IRateService, RateService>(opt => opt.BaseAddress = new Uri("https://www.nbrb.by/api/exrates/rates"));

        //builder.Services.AddTransient<IRateService, RateService>();
        builder.Services.AddSingleton<CurrencyConverter>();

        return builder.Build();
	}
}
