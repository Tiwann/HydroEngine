#include "AudioSystem.h"
#include "Core/Flags.h"
#include "Core/Log.h"
#include "Core/LogVerbosity.h"

#include <fmod/fmod.hpp>
#include <fmod/fmod_errors.h>

#include "Core/Containers/String.h"


#define FMOD_FAILED(Result) (Result) != FMOD_RESULT::FMOD_OK

#define FMOD_CHECK(Result) \
    if(FMOD_FAILED((Result))) \
    { \
        std::string Error = FMOD_ErrorString((Result)); \
        HYDRO_LOG(AudioEngine, Verbosity::Error, "Failed to create audio engine: {}", Error); \
        return false; \
    }((void)0)

namespace FMOD
{
    enum class DebugFlagBits : FMOD_DEBUG_FLAGS
    {
        LevelNone = FMOD_DEBUG_LEVEL_NONE,
        LevelError = FMOD_DEBUG_LEVEL_ERROR,
        LevelWarning = FMOD_DEBUG_LEVEL_WARNING,
        LevelLog = FMOD_DEBUG_LEVEL_LOG,
        TypeMemory = FMOD_DEBUG_TYPE_MEMORY,
        TypeFile = FMOD_DEBUG_TYPE_FILE,
        TypeCodec = FMOD_DEBUG_TYPE_CODEC,
        TypeTrace = FMOD_DEBUG_TYPE_TRACE,
        DisplayTimestamps = FMOD_DEBUG_DISPLAY_TIMESTAMPS,
        DisplayLineNumbers = FMOD_DEBUG_DISPLAY_LINENUMBERS,
        DisplayThread = FMOD_DEBUG_DISPLAY_THREAD,
    };

    HYDRO_DECLARE_FLAGS(DebugFlagBits, DebugFlags);
}
        
namespace Hydro
{
    
    bool AudioSystem::Init(uint32_t SampleRate, uint32_t CallbackBufferSize)
    {
        FMOD_RESULT Result = FMOD::System_Create(&m_Handle);
        FMOD_CHECK(Result);

#if defined(HYDRO_DEBUG)
        FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_WARNING | FMOD_DEBUG_LEVEL_ERROR, FMOD_DEBUG_MODE_CALLBACK, [](
            FMOD_DEBUG_FLAGS flags,
            const char *file,
            int line,
            const char *func,
            const char *message) -> FMOD_RESULT
        {
            FMOD::DebugFlags Flags(flags);
            if(Flags.Contains(FMOD::DebugFlagBits::LevelError))
            {
                HYDRO_LOG(FMOD, Verbosity::Error, "An error occured: File {}. Line {}. Func {}: {}",
                    std::string(file), line, std::string(func), std::string(message));
            }

            if(Flags.Contains(FMOD::DebugFlagBits::LevelWarning))
            {
                HYDRO_LOG(FMOD, Verbosity::Warning, "Warning: File {}. Line {}. Func {}: {}",
                    std::string(file), line, std::string(func), std::string(message));
            }

            return FMOD_OK;
        });
#endif
        Result = m_Handle->setOutput(FMOD_OUTPUTTYPE_AUTODETECT);
        FMOD_CHECK(Result);

        Result = m_Handle->setDSPBufferSize(CallbackBufferSize, 4);
        FMOD_CHECK(Result);

        Result = m_Handle->set3DNumListeners(FMOD_MAX_LISTENERS);
        FMOD_CHECK(Result);

        Result = m_Handle->setSoftwareFormat((int)SampleRate, FMOD_SPEAKERMODE_STEREO, 0);
        FMOD_CHECK(Result);

        Result = m_Handle->init(1024, FMOD_INIT_NORMAL, nullptr);
        FMOD_CHECK(Result);
        
        return true;
    }

    void AudioSystem::Destroy()
    {
        m_Handle->close();
        m_Handle->release();
    }

    void AudioSystem::OnUpdate()
    {
        m_Handle->update();
    }

    FMOD::Sound* AudioSystem::CreateSound(const Path& Filepath, SoundFlags Flags)
    {
        FMOD::Sound* Sound = nullptr;
        const FMOD_RESULT Result = m_Handle->createSound(Filepath.string().c_str(), Flags.As<FMOD_MODE>(), nullptr, &Sound);
        if(Result != FMOD_OK)
        {
            const String Error = FMOD_ErrorString(Result);
            HYDRO_LOG(AudioEngine, Verbosity::Error, "Failed to create sound: {}", Error);
            return nullptr;
        }
        return Sound;
    }
    

    FMOD::System* AudioSystem::GetHandle() const
    {
        return m_Handle;
    }
}
