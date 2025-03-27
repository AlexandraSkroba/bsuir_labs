using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WEB_153504_Skroba.Domain.Entities
{
    public class Cart
    {
        /// <summary>
        /// Список объектов в корзине
        /// key - идентификатор объекта
        /// </summary>
        public Dictionary<int, CartItem> CartItems { get; set; } = new();

        /// <summary>
        /// Добавить объект в корзину
        /// </summary>
        /// <param name="dish">Добавляемый объект</param>
        public virtual void AddToCart(Tea tea)
        {
            if (CartItems.ContainsKey(tea.Id))
            {
                CartItems[tea.Id].Count += 1;
            }
            else
            {
                CartItems.Add(tea.Id, new CartItem { Tea = tea, Count = 1 });
            }
        }

        /// <summary>
        /// Удалить объект из корзины
        /// </summary>
        /// <param name="id"> id удаляемого объекта</param>
        public virtual void RemoveItems(int id)
        {
            if (CartItems.ContainsKey(id))
            {
                CartItems.Remove(id);
            }
        }

        /// <summary>
        /// Очистить корзину
        /// </summary>
        public virtual void ClearAll()
        {
            CartItems.Clear();
        }

        /// <summary>
        /// Количество объектов в корзине
        /// </summary>
        public int Count => CartItems.Sum(item => item.Value.Count);

        /// <summary>
        /// Общая цена
        /// </summary>
        public decimal TotalPrice
        {
            get => CartItems.Sum(item => item.Value.Tea.Price * item.Value.Count);
        }
    }
}
