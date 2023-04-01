using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SmallEngine.Util
{
    interface IVector
    {
        public double X { get; set; }
        public  double Y { get; set; }

        /// <summary>
        /// ベクトルの大きさ
        /// </summary>
        public double Magnitude { get; }

        /// <summary>
        /// ベクトルの大きさ<br/>
        /// Magnitudeよりも、こちらを参照するほうが計算量が小さい。
        /// </summary>
        public double SqrMagnitude { get; }

        /// <summary>
        /// 単位ベクトル
        /// </summary>
        public IVector Normal { get; }

        public void Normalize();
    }

    internal class Vector2 : IVector
    {
        public double X
        {
            get => X;
            set => X = value;
        }

        public double Y
        {
            get => Y;
            set => Y = value;
        }

        // ベクトルの四則演算実装
        public static Vector2 operator +(Vector2 a, Vector2 b) => new Vector2(a.X + b.X, a.Y + b.Y);
        public static Vector2 operator -(Vector2 a, Vector2 b) => new Vector2(a.X - b.X, a.Y - b.Y);
        public static Vector2 operator *(Vector2 a, int b) => new Vector2(a.X * b, a.Y * b);
        public static Vector2 operator *(Vector2 a, long b) => new Vector2(a.X * b, a.Y * b);
        public static Vector2 operator *(Vector2 a, double b) => new Vector2(a.X * b, a.Y * b);
        public static Vector2 operator *(Vector2 a, float b) => new Vector2(a.X * b, a.Y * b);
        public static Vector2 operator /(Vector2 a, int b) => new Vector2(a.X / b, a.Y / b);
        public static Vector2 operator /(Vector2 a, long b) => new Vector2(a.X / b, a.Y / b);
        public static Vector2 operator /(Vector2 a, double b) => new Vector2(a.X / b, a.Y / b);
        public static Vector2 operator /(Vector2 a, float b) => new Vector2(a.X / b, a.Y / b);

        /// <summary>
        /// ベクトルの大きさ
        /// </summary>
        public double Magnitude 
        {
            get
            {
                return Math.Sqrt(SqrMagnitude);
            }
            private set { }
        }

        /// <summary>
        /// ベクトルの大きさ<br/>
        /// Magnitudeよりも、こちらを参照するほうが計算量が小さい。
        /// </summary>
        public double SqrMagnitude
        {
            get
            {
                return Math.Pow(X, 2) + Math.Pow(Y, 2);
            }
        }

        /// <summary>
        /// 単位ベクトル
        /// </summary>
        public IVector Normal
        {
            get
            {
                return this / Magnitude;
            }
            private set { }
        }

        Vector2() : this(0, 0) { }

        Vector2(double X, double Y)
        {
            this.X = X;
            this.Y = Y;
        }

        /// <summary>
        /// ベクトルを正規化する
        /// </summary>
        public void Normalize()
        {
            X /= Magnitude;
            Y /= Magnitude;
        }

        /// <summary>
        /// ベクトルの内積を求める
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns>aとbの内積</returns>
        public static double Dot(Vector2 a, Vector2 b)
        {
            return a.X * b.X + a.Y * b.Y;
        }
    }

    internal class Vector3 : IVector
    {
        public double X
        {
            get => X;
            set => X = value;
        }

        public double Y
        {
            get => Y;
            set => Y = value;
        }

        public double Z;

        // ベクトルの四則演算実装
        public static Vector3 operator +(Vector3 a, Vector3 b) => new Vector3(a.X + b.X, a.Y + b.Y, a.Z * b.Z);
        public static Vector3 operator -(Vector3 a, Vector3 b) => new Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
        public static Vector3 operator *(Vector3 a, int b) => new Vector3(a.X * b, a.Y * b, a.Z * b);
        public static Vector3 operator *(Vector3 a, long b) => new Vector3(a.X * b, a.Y * b, a.Z * b);
        public static Vector3 operator *(Vector3 a, double b) => new Vector3(a.X * b, a.Y * b, a.Z * b);
        public static Vector3 operator *(Vector3 a, float b) => new Vector3(a.X * b, a.Y * b, a.Z * b);
        public static Vector3 operator /(Vector3 a, int b) => new Vector3(a.X / b, a.Y / b, a.Z / b);
        public static Vector3 operator /(Vector3 a, long b) => new Vector3(a.X / b, a.Y / b, a.Z / b);
        public static Vector3 operator /(Vector3 a, double b) => new Vector3(a.X / b, a.Y / b, a.Z / b);
        public static Vector3 operator /(Vector3 a, float b) => new Vector3(a.X / b, a.Y / b, a.Z / b);

        /// <summary>
        /// ベクトルの大きさ
        /// </summary>
        public double Magnitude
        {
            get
            {
                return Math.Sqrt(SqrMagnitude);
            }
            private set { }
        }

        /// <summary>
        /// ベクトルの大きさ<br/>
        /// Magnitudeよりも、こちらを参照するほうが計算量が小さい。
        /// </summary>
        public double SqrMagnitude
        {
            get
            {
                return Math.Pow(X, 2) + Math.Pow(Y, 2) + Math.Pow(Z, 2);
            }
        }

        /// <summary>
        /// 単位ベクトル
        /// </summary>
        public IVector Normal
        {
            get
            {
                return this / Magnitude;
            }
            private set { }
        }

        /// <summary>
        /// ベクトルを正規化する
        /// </summary>
        public void Normalize()
        {
            X /= Magnitude;
            Y /= Magnitude;
            Z /= Magnitude;
        }

        Vector3() : this(0, 0, 0) { }
        Vector3(double X, double Y, double Z)
        {
            this.X = X;
            this.Y = Y;
            this.Z = Z;
        }

        /// <summary>
        /// ベクトルの内積を求める
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns>aとbの内積</returns>
        public static double Dot(Vector3 a, Vector3 b)
        {
            return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
        }

        /// <summary>
        /// ベクトルの外積を求める
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns>aとbの外積</returns>
        public static Vector3 Cross(Vector3 a, Vector3 b)
        {
            return new Vector3(
                a.Y * b.Z - a.Z * b.Y, 
                a.Z * b.X - a.X * b.Z,
                a.X * b.Y - a.Y * b.X
                );
        }
    }
}
