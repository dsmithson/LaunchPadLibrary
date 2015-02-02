using namespace System; 

namespace Knightware
{
	namespace IO
	{
		namespace Devices
		{
			public ref class KBoardBendChangedEventArgs : EventArgs
			{
			public:
				unsigned char BendValue;
			};

			public delegate void KBoardBendChangedEventHandler(Object^ sender, KBoardBendChangedEventArgs^ e);
		}
	}
}