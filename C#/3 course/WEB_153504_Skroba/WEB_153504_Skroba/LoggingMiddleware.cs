using Serilog;
using System;

namespace WEB_153504_Skroba
{
    public class LoggingMiddleware
    {
            private readonly RequestDelegate _next;

            public LoggingMiddleware(RequestDelegate next)
            {
                /*следующий компонент в конвейере запроса / ответа*/
                _next = next;
            }

        /*если статус код ответа не в пределах 2xx, генерируется лог с информацией о запросе и ответе*/
            public async Task InvokeAsync(HttpContext context)
            {
                await _next(context);

                var response = context.Response;
                var statusCode = response.StatusCode;

                if (statusCode < 200 || statusCode >= 300)
                {
                    var request = context.Request;
                    var message = $"{DateTimeOffset.Now} [{context.TraceIdentifier}] ---> request {request.Path}{request.QueryString} returns {statusCode}";

                    Log.Logger.Information(message);
                }
            }
        }

    /*расширение для IApplicationBuilder, который добавляет LoggingMiddleware в конвейер обработки запросов*/
        public static class LoggingMiddlewareExtensions
        {
            public static IApplicationBuilder UseLoggingMiddleware(this IApplicationBuilder builder)
            {
                return builder.UseMiddleware<LoggingMiddleware>();
            }
        }
    }
