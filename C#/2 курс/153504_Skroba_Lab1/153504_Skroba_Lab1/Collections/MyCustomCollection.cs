using System.Collections;
using _153504_Skroba_Lab1.Interfaces;
using _153504_Skroba_Lab1.Entities;

namespace _153504_Skroba_Lab1.Collections
{
    class Node<T>
    {
        public Node(T data) 
        { 
            Data = data;
        }
        public Node<T> Next { get; set; } = null; 
        public T Data { get; set; }
    }
    internal class MyCustomCollection<T> : ICustomCollection<T>, IEnumerable
    {
        private Node<T> head;
        private Node<T> tail;
        private Node<T> current;

        private int count;

        public MyCustomCollection()
        {
            head = null;
            tail = null;
            current = null;
            count = 0;
        }

        public T this[int index] {
            get
            {
                Reset();
                int currentIndex = 0;
                var buffCurrent = head;

                while (currentIndex != index && buffCurrent != null)
                {
                    currentIndex++;
                    buffCurrent = buffCurrent.Next;
                }

                if (currentIndex == index && buffCurrent.Data != null)
                {
                    return buffCurrent.Data;
                }

                throw new IndexOutOfRangeException(); // генерируется, если индекс элемента массива или коллекции находится вне диапазона допустимых значений
            }
            set
            {
                Reset();
                int currentIndex = 0;
                var buffCurrent = head;

                while (currentIndex != index && buffCurrent!=null)
                {
                    currentIndex++;
                    buffCurrent = buffCurrent.Next;
                }

                if (currentIndex == index)
                {
                    buffCurrent.Data = value;
                }

                throw new IndexOutOfRangeException();
            }
        }

        public void Reset()
        {
            current = head;
        }

        public void Next()
        {
            if (current.Next != null)
            {
                current = current.Next;
            }
            else
            {
                Reset();
            }
        }

        public T Current()
        {
            if (current != null)
            {
                return current.Data;
            }

            throw new NullReferenceException(); // генерируется при попытке обращения к объекту, который равен null
        }

        public int Count
        {
            get 
            {
                return count;
            }
        }

        public void Add(T item)
        {
            Node<T> node = new Node<T>(item);

            if (head == null)
            {
                head = node;
                tail = node;
                current = node;
                count++;
            }
            else
            {
                tail.Next = node;
                tail = tail.Next;
                count++;
            }
        }

        public void Remove(T item)
        {
            if (head != null)
            {
                var buffCurrent = head;
                var buffNext = buffCurrent.Next;

                if (head.Data.Equals(item))
                {
                    head = buffNext;
                    count--;

                    Reset();

                    if (count == 0)
                    {
                        current = null;
                        tail = null;
                    }

                    return;
                }

                while (buffNext != null)
                {
                    if (buffNext.Data.Equals(item))
                    {
                        buffCurrent.Next = buffNext.Next;
                        count--;

                        if (count == 0)
                        {
                            current = null;
                            tail = null;
                        }
                        else if (buffNext.Next == null)
                        {
                            tail = buffCurrent;
                        }

                        Reset();

                        return;
                    }
                    else
                    {
                        buffCurrent = buffNext;
                        buffNext = buffCurrent.Next;
                    }
                }
            }

            throw new MyException("Element to be removed is missing!"); 
        }

        public T RemoveCurrent()
        {
            if (current != null)
            {
                var item = current.Data;
                Remove(item);

                return item;
            }

            throw new NullReferenceException();
        }

        public IEnumerator GetEnumerator()
        {
            var buff = head;

            while(buff != null)
            {
                yield return buff.Data;

                buff = buff.Next;
            }
        }
    }
}
