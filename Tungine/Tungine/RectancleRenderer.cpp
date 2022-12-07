#include "RectangleRenderer.h"

void RectangleRenderer::Render(SDL_Renderer* renderer)
{
	rect = SDL_Rect{transform.getX(), transform.getY(), (int)height, (int)width};
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rect);
}