#ifndef RENDERERFACTORY_HXX
#define RENDERERFACTORY_HXX

#include <memory>
#include "Renderer.hxx"

class RendererFactory
{
public:
  using RendererPtr = std::shared_ptr<Renderer>;  
  static RendererPtr Create(std::string const& pType);
};

#endif
