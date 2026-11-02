#ifndef CX_SPRITE_ANIMATION_MANAGER_HPP
#define CX_SPRITE_ANIMATION_MANAGER_HPP

#include "CX/Sprite/Animation.hpp"
#include <string>

namespace cx
{
   /// @brief Push a new animation to the internal manager.
   /// @param name Name of the animation.
   /// @param animation The animation.
   /// @return ID of animation.
   size_t push_animation(const std::string &name, const Animation &animation);

   /// @brief Push a new animation to the internal manager. If it already exists, override it.
   /// @param name Name of the animation.
   /// @param animation The animation.
   /// @return ID of animation.
   size_t push_animation_override(const std::string &name, const Animation &animation);

   /// @brief Get an animation by name.
   /// @param name Name of the animation.
   /// @return Animation.
   const Animation &get_animation_by_name(const std::string &name);

   /// @brief Get an animation by ID.
   /// @param id ID of the animation.
   /// @return Animation.
   const Animation &get_animation_by_id(size_t id);

   /// @brief Check whether an animation with the given name exists.
   /// @param name Name of the animation.
   /// @return True if exists, otherwise false.
   bool animation_exists_by_name(const std::string &name);

   /// @brief Check whether an animation with the given ID exists.
   /// @param id ID of the animation.
   /// @return True if exists, otherwise false.
   bool animation_exists_by_id(size_t id);

   /// @brief Edit an animation with the given name.
   /// @param name Name of the animation.
   /// @param animation New animation.
   void edit_animation_by_name(const std::string &name, const Animation &animation);

   /// @brief Edit an animation with the given ID.
   /// @param id ID of the animation.
   /// @param animation New animation.
   void edit_animation_by_id(size_t id, const Animation &animation);

   /// @brief Get current animation count.
   /// @return Animation count.
   size_t get_animation_count();
   
   /// @brief Clear all animations. This will invalidate all IDs.
   void clear_animations();
}

#endif
