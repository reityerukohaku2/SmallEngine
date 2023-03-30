using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SmallEngine.Util
{
    internal class Vector2
    {
        public double x, y;

        // ベクトルの四則演算実装
        public static Vector2 operator +(Vector2 a, Vector2 b) => new Vector2(a.x + b.x, a.y + b.y);
        public static Vector2 operator -(Vector2 a, Vector2 b) => new Vector2(a.x - b.x, a.y - b.y);
        public static Vector2 operator *(Vector2 a, int b) => new Vector2(a.x * b, a.y * b);
        public static Vector2 operator *(Vector2 a, long b) => new Vector2(a.x * b, a.y * b);
        public static Vector2 operator *(Vector2 a, double b) => new Vector2(a.x * b, a.y * b);
        public static Vector2 operator *(Vector2 a, float b) => new Vector2(a.x * b, a.y * b);
        public static Vector2 operator /(Vector2 a, int b) => new Vector2(a.x / b, a.y / b);
        public static Vector2 operator /(Vector2 a, long b) => new Vector2(a.x / b, a.y / b);
        public static Vector2 operator /(Vector2 a, double b) => new Vector2(a.x / b, a.y / b);
        public static Vector2 operator /(Vector2 a, float b) => new Vector2(a.x / b, a.y / b);

        /// <summary>
        /// ベクトルの大きさ
        /// </summary>
        public double magnitude 
        {
            get
            {
                return Math.Sqrt(sqrMagnitude);
            }
            private set { }
        }

        /// <summary>
        /// ベクトルの大きさ<br/>
        /// magnitudeよりも、こちらを参照するほうが計算量が小さい。
        /// </summary>
        public double sqrMagnitude
        {
            get
            {
                return Math.Pow(x, 2) + Math.Pow(y, 2);
            }
        }

        public Vector2 normal
        {
            get
            {
                return this / magnitude;
            }
            private set { }
        }

        Vector2() : this(0, 0) { }

        Vector2(double x, double y)
        {
            this.x = x;
            this.y = y;
        }

        /// <summary>
        /// ベクトルを正規化する
        /// </summary>
        public void Normalize()
        {
            x /= magnitude;
            y /= magnitude;
        }

        /// <summary>
        /// ベクトルの内積を求める
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns>aとbの内積</returns>
        public static double Dot(Vector2 a, Vector2 b)
        {
            return a.x * b.x + a.y * b.y;
        }

        /// <summary>
        /// ベクトルの外積を求める
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns>aとbの外積</returns>
        public static double Cross(Vector2 a, Vector2 b)
        {
            return new Vector2();
        }
    }
}
