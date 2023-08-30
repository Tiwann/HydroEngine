#pragma once

#include "BinarySerializer.h"
#include "Core/Scene.h"

namespace Hydro
{
   class SceneSerializer : public BinarySerializer<Scene>
   {
   public:
      SceneSerializer(std::string&& filepath);

      bool Serialize(const Scene&) override;
      bool Deserialize(Scene&) override;

   private:
      
   };
}
