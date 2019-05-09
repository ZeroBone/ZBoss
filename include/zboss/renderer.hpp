#ifndef ZBOSS_RENDERER_HPP
#define ZBOSS_RENDERER_HPP

#include <zboss/assets/loaders/texture.hpp>
#include <zboss/assets/loaders/font.hpp>
#include <zboss/math/vector.hpp>
#include <zboss/math/shape.hpp>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <functional>

namespace zboss {

    using DrawRequest = std::function<bool()>;

    class Renderer {

        public:

        void setSdlRenderer(SDL_Renderer* rdr);

        bool renderClear();

        void present();

        bool draw_point(const Vector2D& pos, const SDL_Color& color);

        bool drawLine(const Vector2D& start, const Vector2D& end, const SDL_Color& color);

        bool drawRectangle(const SDL_Rect& r, const SDL_Color& color);

        bool drawRectangle(const SDL_Rect& r, float angle, const SDL_Color& color);

        bool draw_filled_rect(const SDL_Rect& r, const SDL_Color& color);

        bool draw_filled_rect(const SDL_Rect& r, float angle, const SDL_Color& color);

        bool draw_circle(const Vector2D& center, int radius, const SDL_Color& color);

        bool draw_filled_circle(const Vector2D& center, int radius, const SDL_Color& color);

        bool draw_ellipse(const Vector2D& center, int hradius, int vradius, const SDL_Color& color);

        bool draw_ellipse(const Vector2D& center, int hradius, int vradius, float angle, const SDL_Color& color);

        bool draw_ellipse(const Vector2D& center, int hradius, int vradius, SDL_RendererFlip flip, const SDL_Color& color);

        bool draw_ellipse(const Vector2D& center, int hradius, int vradius, float angle, SDL_RendererFlip flip,
                          const SDL_Color& color);

        bool draw_filled_ellipse(const Vector2D& center, int hradius, int vradius, const SDL_Color& color);

        bool draw_filled_ellipse(const Vector2D& center, int hradius, int vradius, float angle, const SDL_Color& color);

        bool draw_filled_ellipse(const Vector2D& center, int hradius, int vradius, SDL_RendererFlip flip,
                                 const SDL_Color& color);

        bool renderEllipseFilled(const Vector2D& center, int hradius, int vradius, float angle, SDL_RendererFlip flip,
                                 const SDL_Color& color);

        bool draw_shape(const Shape& shape, const SDL_Color& color);

        bool draw_filled_shape(const Shape& shape, const SDL_Color& color);

        bool drawTexture(std::shared_ptr<TextureAsset> asset, const SDL_Rect& dest);

        bool drawTexture(std::shared_ptr<TextureAsset> asset, const SDL_Rect& src, const SDL_Rect& dest);

        bool drawTexture(std::shared_ptr<TextureAsset> asset, const SDL_Rect& dest, float angle, const SDL_Point& center,
                         SDL_RendererFlip flip);

        bool drawTexture(std::shared_ptr<TextureAsset> asset, const SDL_Rect& src, const SDL_Rect& dest, float angle,
                         const SDL_Point& center, SDL_RendererFlip flip);

        bool renderText(std::shared_ptr<Font> asset, const std::string& text, const Vector2D& pos, const SDL_Color& color);

        std::string get_error() const;

        private:

        bool draw_with_color(DrawRequest req, const SDL_Color& color);

        bool renderTargeted(DrawRequest req, float angle, const SDL_Point& center, SDL_RendererFlip flip);

        void setError(const std::string& text);

        public:

        SDL_Renderer* renderer;

        void destroy() {

            SDL_DestroyRenderer(renderer);

        }

        private:

        std::string error;

    };
}

#endif //ZBOSS_RENDERER_HPP