#include <iostream>
#include <vorbis/vorbisfile.h>
#include <AL/al.h>
#include <AL/alc.h>

// Function to initialize OpenAL
void initializeOpenAL(ALCdevice** device, ALCcontext** context) {
    *device = alcOpenDevice(nullptr);
    if (!(*device)) {
        std::cerr << "Error: Failed to open OpenAL device." << std::endl;
        exit(EXIT_FAILURE);
    }

    *context = alcCreateContext(*device, nullptr);
    if (!(*context)) {
        std::cerr << "Error: Failed to create OpenAL context." << std::endl;
        exit(EXIT_FAILURE);
    }

    alcMakeContextCurrent(*context);
}

// Function to clean up OpenAL resources
void cleanUpOpenAL(ALCdevice* device, ALCcontext* context) {
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

int main() {
    const char* filename = "/home/yash.soni/Personal/reader_app/Example.ogg";

    ALCdevice* device;
    ALCcontext* context;

    // Initialize OpenAL
    initializeOpenAL(&device, &context);

    // Load the Ogg file
    OggVorbis_File oggFile;
    if (ov_fopen(filename, &oggFile) != 0) {
        std::cerr << "Error: Failed to open Ogg file." << std::endl;
        cleanUpOpenAL(device, context);
        exit(EXIT_FAILURE);
    }

    // Get Ogg file info
    vorbis_info* vorbisInfo = ov_info(&oggFile, -1);
    int channels = vorbisInfo->channels;
    int rate = vorbisInfo->rate;

    // Allocate a buffer for audio data
    const int bufferSize = 4096;
    char buffer[bufferSize];
    int bitstream;

    // Create OpenAL audio buffer and source
    ALuint audioBuffer;
    alGenBuffers(1, &audioBuffer);

    ALuint audioSource;
    alGenSources(1, &audioSource);

    // Decode and play the audio
    while (true) {
        long bytesRead = ov_read(&oggFile, buffer, bufferSize, 0, 2, 1, &bitstream);
        if (bytesRead <= 0) {
            break; // End of file or error
        }

        // Upload the audio data to the OpenAL buffer
        alBufferData(audioBuffer, AL_FORMAT_STEREO16, buffer, static_cast<ALsizei>(bytesRead), rate);

        // Link the buffer to the audio source and play it
        alSourcei(audioSource, AL_BUFFER, audioBuffer);
        alSourcePlay(audioSource);

        // Wait until the sound has finished playing
        ALint sourceState;
        do {
            alGetSourcei(audioSource, AL_SOURCE_STATE, &sourceState);
        } while (sourceState == AL_PLAYING);
    }

    // Clean up resources
    ov_clear(&oggFile);
    alDeleteSources(1, &audioSource);
    alDeleteBuffers(1, &audioBuffer);
    cleanUpOpenAL(device, context);

    return 0;
}

