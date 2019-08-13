#ifndef BASEGAME_H
#define BASEGAME_H

#define DLLEXPORT __declspec(dllexport)

namespace Basegame
{
	class DLLEXPORT BaseGame
	{
	private:
	public:
		void MostrarAlgo();
		int OpenWindow();
	};
}

#endif
