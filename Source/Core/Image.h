#pragma once
#include "HydroPCH.h"
#include "Buffer.h"
#include "SharedPointer.h"
#include "Filesystem.h"

#include <string>
namespace Hydro {

	using ImageFormat = enum
	{
		RGBA8,
		RGBA16,
		RGBA32F
	};

	static constexpr std::string FormatToString(ImageFormat Format)
	{
		switch (Format) {
		case RGBA8: return "RGBA8 (Unsigned Bytes)";
		case RGBA16: return "RGBA16 (Unsigned Shorts)";
		case RGBA32F: return "RGBA32F (Floats)";
		}
		return "";
	}
	
	class Image
	{
	public:
		Image(uint32_t Width, uint32_t Height, ImageFormat Format, const void* Pixels)
			: m_Width(Width), m_Height(Height), m_Format(Format)
		{
			const size_t Size = m_Format == RGBA8 ? 1 : m_Format == RGBA16 ? 2 : 4;
			m_Pixels = malloc(m_Width * m_Height * 4 * Size);
			std::copy_n((uint8_t*)Pixels, Size, (uint8_t*)m_Pixels);
		}

		Image(const std::filesystem::path& filepath, ImageFormat format);
		Image(const Buffer<uint8_t>& buffer, ImageFormat format);
		Image(const BufferView<uint8_t>& buffer, ImageFormat format);
		~Image();
		
		static Ref<Image> Create(const Path& Filepath, ImageFormat Format);
		static Ref<Image> Create(const Buffer<uint8_t>& Buffer, ImageFormat Format);
		static Ref<Image> Create(const BufferView<uint8_t>& BufferView, ImageFormat Format);
		
		ImageFormat GetFormat() const;
		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
		size_t GetSize() const;
		const void* GetData() const;
		void* GetData();
		bool Valid() const;
	
	private:
		uint32_t m_Width{0}, m_Height{0};
		ImageFormat m_Format{RGBA8};
		void* m_Pixels{nullptr};
	};
}
