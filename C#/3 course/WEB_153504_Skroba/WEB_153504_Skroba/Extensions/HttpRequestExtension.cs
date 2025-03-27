namespace WEB_153504_Skroba.Extensions
{
	public static class HttpRequestExtension
	{
        public static bool IsAjaxRequest(this HttpRequest request)
        {
            return request.Headers["X-Requested-With"] == "XMLHttpRequest";
        }
    }
}
