#include "CX/Sprite/AnimationManager.hpp"
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace cx
{
   static std::unordered_map<std::string, size_t> animationIds;
   static std::vector<Animation> animations;

   size_t push_animation(const std::string &name, const Animation &animation)
   {
      if (auto it = animationIds.find(name); it != animationIds.end())
      {
         return it->second;
      }
      size_t id = animations.size();
      animationIds[name] = id;
      animations.push_back(animation);
      return id;
   }

   size_t push_animation_override(const std::string &name, const Animation &animation)
   {
      if (auto it = animationIds.find(name); it != animationIds.end())
      {
         size_t id = it->second;
         animations[id] = animation;
         return id;
      }
      size_t id = animations.size();
      animationIds[name] = id;
      animations.push_back(animation);
      return id;
   }

   const Animation &get_animation_by_name(const std::string &name)
   {
      if (auto it = animationIds.find(name); it != animationIds.end())
      {
         return animations[it->second];
      }
      throw std::runtime_error("CX::get_animation_by_name: Animation '" + name + "' does not exist!");
   }

   const Animation &get_animation_by_id(size_t id)
   {
      if (id >= animations.size())
      {
         throw std::runtime_error("CX::get_animation_by_id: Animation with ID " + std::to_string(id) + " does not exist!");
      }
      return animations[id];
   }

   bool animation_exists_by_name(const std::string &name)
   {
      return animationIds.contains(name);
   }

   bool animation_exists_by_id(size_t id)
   {
      return id < animations.size();
   }

   void edit_animation_by_name(const std::string &name, const Animation &animation)
   {
      if (auto it = animationIds.find(name); it != animationIds.end())
      {
         animations[it->second] = animation;
         return;
      }
      throw std::runtime_error("CX::edit_animation_by_name: Animation '" + name + "' does not exist!");
   }

   void edit_animation_by_id(size_t id, const Animation &animation)
   {
      if (id >= animations.size())
      {
         throw std::runtime_error("CX::edit_animation_by_id: Animation with ID " + std::to_string(id) + " does not exist!");
      }
      animations[id] = animation;
   }

   size_t get_animation_count() {
      return animations.size();
   }

   void clear_animations()
   {
      animationIds.clear();
      animations.clear();
   }
}
