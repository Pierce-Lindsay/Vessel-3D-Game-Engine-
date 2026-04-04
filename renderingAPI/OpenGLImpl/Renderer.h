#pragma once
#include "IRenderer.h"

namespace ve
{
	class RendererOpenGL : public IRenderer
	{
	public:
		RendererOpenGL();
		~RendererOpenGL();
		void Render() override;
		bool Init() override;
		bool ShutDown() override;
	};
}