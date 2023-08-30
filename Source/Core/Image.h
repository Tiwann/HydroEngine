#pragma once
#include "HydroPCH.h"
#include "Buffer.h"

enum class ImageFormat;

namespace Hydro {
	class HYDRO_API Image
	{
	public:
		Image();
		explicit Image(const std::filesystem::path& filepath);
		Image(const std::filesystem::path& filepath, ImageFormat format);
		explicit Image(const Buffer<uint8_t>& buffer);
		Image(const uint8_t* buffer, size_t size);
		Image(const uint8_t* buffer, size_t size, ImageFormat format);
		~Image();

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
		const void* GetData() const;
		void* GetData();
	
	private:
		uint32_t m_Width{0}, m_Height{0};
		ImageFormat m_Format{0};
		void* m_Pixels;
	};
}