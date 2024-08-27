#pragma once
#include "Buffer.h"
#include "SharedPointer.h"
#include "Filesystem.h"

#include <string>
namespace Hydro {

	enum class ImageFormat
	{
		RGBA8,
		RGBA16,
		RGBA32F
	};

	static constexpr std::string FormatToString(ImageFormat Format)
	{
		switch (Format) {
		case ImageFormat::RGBA8: return "RGBA8 (Unsigned Bytes)";
		case ImageFormat::RGBA16: return "RGBA16 (Unsigned Shorts)";
		case ImageFormat::RGBA32F: return "RGBA32F (Floats)";
		}
		return "";
	}
	
	class Image
	{
	public:
		Image(uint32_t Width, uint32_t Height, ImageFormat Format, const void* Pixels);

		Image(const Path& Filepath, ImageFormat Fmt);
		Image(const Buffer<uint8_t>& Buffer, ImageFormat Fmt);
		Image(const BufferView<uint8_t>& Buffer, ImageFormat Fmt);
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
		ImageFormat m_Format{ImageFormat::RGBA8};
		void* m_Pixels{nullptr};
	};
}
