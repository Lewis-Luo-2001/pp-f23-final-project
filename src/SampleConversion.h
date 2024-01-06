#pragma once

/**
 * Compress samples and convert to suitable data structure
 *
 * @param samples original samples
 * @param num_channels number of channels
 * @param num_samples number of samples
 * @param length_in_seconds length of audio
 */
std::vector<AudioType> sample_conversion(const AudioBuffer &samples, int num_channels, int num_samples, double length_in_seconds);
