﻿/* класс, описывающий формат данных, получаемых от сервисов */

namespace WEB_153504_Skroba.Domain.Models
{
	public class ResponseData<T>
	{
		// запрашиваемые данные
		public T? Data { get; set; }
		// признак успешного завершения запроса
		public bool Success { get; set; } = true;
		// сообщение в случае неуспешного завершения
		public string? ErrorMessage { get; set; }
	}
}
