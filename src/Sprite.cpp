#include "CX/Sprite/Sprite.hpp"

namespace cx
{
   /// Set default styles

   std::unique_ptr<SpriteStyle> SpriteStyle::style1_t;
   std::unique_ptr<SpriteStyle> SpriteStyle::style2_t;
   std::unique_ptr<SpriteStyle> SpriteStyle::style3_t;

   static const std::string empty_string;

   // Constructors

   Sprite::Sprite() {}

   Sprite::Sprite(const SpriteStyle& style)
   {
      rect.setSize(style.size);
      rect.setOrigin(style.size * .5f);
      rect.setFillColor(style.color);
      rect.setTexture(style.texture.get());

      if (!style.texture_rect.empty())
         rect.setTextureRect(style.texture_rect);
   }

   Sprite::Sprite(const Vec2f& size,
                  const Vec2f& position,
                  const sf::Texture* texture,
                  const Vec4i& texture_rect)
   {
      rect.setPosition(position);
      rect.setSize(size);
      rect.setOrigin(size * .5f);
      rect.setTexture(texture);

      if (!texture_rect.empty())
         rect.setTextureRect(texture_rect);
   }

   // Constructors after creation

   void Sprite::create(const SpriteStyle& style)
   {
      rect.setSize(style.size);
      rect.setOrigin(style.size * .5f);
      rect.setFillColor(style.color);
      rect.setTexture(style.texture.get());

      if (!style.texture_rect.empty())
         rect.setTextureRect(style.texture_rect);
   }

   void Sprite::create(const Vec2f& size,
                       const Vec2f& position,
                       const sf::Texture* texture,
                       const Vec4i& textureRect)
   {
      rect.setPosition(position);
      rect.setSize(size);
      rect.setOrigin(size * .5f);
      rect.setTexture(texture);

      if (!textureRect.empty())
         rect.setTextureRect(textureRect);
   }

   // Setter functions

   void Sprite::set_center(const Vec2f& position)
   {
      rect.setPosition(position);   
   }

   void Sprite::set_scale(const Vec2f& scale)
   {
      rect.setScale(scale);
   }

   void Sprite::set_size(const Vec2f& size)
   {
      rect.setSize(size);
      rect.setOrigin(size * .5f);
   }

   void Sprite::set_rotation(float angle)
   {
      rect.setRotation(angle);
   }

   void Sprite::set_texture(const sf::Texture* texture)
   {
      rect.setTexture(texture);
   }

   void Sprite::set_texture_rect(const Vec4i& rect_)
   {
      rect.setTextureRect(rect_);
   }

   void Sprite::set_color(const Color& color)
   {
      rect.setFillColor(color);
   }

   // Getter functions

   ElementType Sprite::get_element_type() const
   {
      return ElementType::sprite;
   }

   Vec2f Sprite::get_center() const
   {
      return rect.getPosition();
   }

   Vec2f Sprite::get_scale() const
   {
      return rect.getScale();
   }

   Vec2f Sprite::get_size() const
   {
      return get_scale().abs() * rect.getSize();
   }

   Vec2f Sprite::get_origin() const
   {
      return get_scale().abs() * rect.getOrigin();
   }

   Deg Sprite::get_rotation() const
   {
      return rect.getRotation();
   }

   const sf::Texture* Sprite::get_texture() const
   {
      return rect.getTexture();
   }

   Vec4i Sprite::get_texture_rect() const
   {
      return rect.getTextureRect();
   }

   Color Sprite::get_color() const
   {
      return rect.getFillColor();
   }

   // Update functions

   void Sprite::update(const MouseState& state, bool local)
   {
      update_state(state, local);
   }

   void Sprite::update_all(float dt, const MouseState& state, bool local)
   {
      update_state(state, local);
      update_animation(dt);
   }

   void Sprite::update_animation(float dt)
   {
      if (!playing || !animation_exists_by_id(current_anim))
         return;

      elapsedTime += dt;

      if (elapsedTime * speedMult >= get_animation_by_id(current_anim).speed)
         advance_frame();
   }

   void Sprite::play()
   {
      if (current_anim != std::string::npos)
         playing = true;
   }

   void Sprite::pause()
   {
      if (current_anim != std::string::npos)
         playing = false;
   }

   void Sprite::reset()
   {
      playing = default_anim != std::string::npos;
      frame = 0;
      elapsedTime = 0.f;

      if (animation_exists_by_id(current_anim))
      {
         const Animation &anim = get_animation_by_id(current_anim);
         rect.setTextureRect(Vec4i(anim.posX, anim.posY, anim.sizeX, anim.sizeY));
      }

      current_anim = default_anim;
   }

   void Sprite::advance_frame()
   {
      if (!animation_exists_by_id(current_anim))
         return;
      const Animation &anim = get_animation_by_id(current_anim);

      elapsedTime = 0.f;

      if (anim.reversed)
         frame = (frame - 1 + anim.length) % anim.length;
      else
         frame = (frame + 1) % anim.length;

      rect.setTextureRect(Vec4i(
         anim.posX + (anim.gap + anim.sizeX) * (unsigned)frame,
         anim.posY + (anim.gap + anim.sizeY) * (unsigned)frameY,
         anim.sizeX,
         anim.sizeY
      ));

      if (!(frame == anim.length - 1 && !anim.reversed) && !(frame == 0 && anim.reversed))
         return;

      if (anim.looping)
         return;

      elapsedTime = 0.f;
      frame = 0;

      rect.setTextureRect(Vec4i(anim.posX, anim.posY, anim.sizeX, anim.sizeY));

      if (animation_exists_by_id(default_anim))
         current_anim = default_anim;
      else
      {
         playing = false;
         current_anim = std::string::npos;
      }
   }

   void Sprite::set_frame_y(size_t frame)
   {
      frameY = frame;
   }

   void Sprite::set_default_animation(size_t id)
   {
      current_anim = default_anim = id;
      playing = true;
   }

   void Sprite::play_animation(size_t id, bool reset)
   {
      if (!reset && id == current_anim)
         return;

      if (animation_exists_by_id(id) && (current_anim != id || !get_animation_by_id(id).looping))
      {
         frame = 0;
         elapsedTime = 0.f;
      }

      current_anim = id;
      playing = true;
   }

   bool Sprite::is_animation_finished() const
   {
      return !playing && current_anim == std::string::npos;
   }

   bool Sprite::is_default_playing() const
   {
      return playing && animation_exists_by_id(current_anim) && current_anim == default_anim;
   }

   bool Sprite::is_playing() const
   {
      return playing && animation_exists_by_id(current_anim);
   }

   bool Sprite::is_paused() const
   {
      return !playing && animation_exists_by_id(current_anim);
   }

   void Sprite::set_speed_multiplier(float multiplier)
   {
      speedMult = multiplier;
   }

   size_t Sprite::get_frame_index() const
   {
      return frame;
   }

   size_t Sprite::get_frame_y() const
   {
      return frameY;
   }

   float Sprite::get_speed_multiplier() const
   {
      return speedMult;
   }

   size_t Sprite::get_playing_animation() const
   {
      return current_anim;
   }

   size_t Sprite::get_default_animation() const
   {
      return default_anim;
   }

   void Sprite::clear_animations()
   {
      playing = false;
      frame = 0;
      elapsedTime = 0.f;
      current_anim = default_anim = std::string::npos;
   }

   // Render functions

   void Sprite::render(sf::RenderWindow& window) const
   {
      window.draw(rect);
   }

   void Sprite::render(sf::RenderWindow& window, const sf::Shader* shader) const
   {
      window.draw(rect, shader);
   }

   // Access functions

   sf::RectangleShape& Sprite::get_sprite()
   {
      return rect;
   }

   const sf::RectangleShape& Sprite::get_sprite() const
   {
      return rect;
   }
}
