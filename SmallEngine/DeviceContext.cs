using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SmallEngine
{
    internal class DeviceContext : IDeviceContext
    {
        public void Dispose()
        {
            throw new NotImplementedException();
        }

        public IntPtr GetHdc()
        {
            throw new NotImplementedException();
        }

        public void ReleaseHdc()
        {
            throw new NotImplementedException();
        }
    }
}
