#include <gtest/gtest.h>
#include <iostream>

#include "sio/base.h"
#include "sio/audio.h"
#include "sio/mean_var_norm.h"
#include "sio/feature.h"

namespace sio {

TEST(Feature, ExtractorAndMeanVarNorm) {
  Map<Str, int> audio_to_frames = {
    {"testdata/MINI/audio/audio1.wav", 126},
    {"testdata/MINI/audio/audio2.wav", 522}
  };

  FeatureExtractorConfig config;
  config.type = "fbank";
  config.fbank.frame_opts.samp_freq = 16000;
  config.fbank.frame_opts.dither = 1.0;
  config.fbank.mel_opts.num_bins = 80;
  config.mean_var_norm_file = "testdata/mean_var_norm.txt";

  FeatureExtractor feature_extractor(config);
  for (const auto& kv : audio_to_frames) {
    Str audio_file = kv.first;
    int num_frames = kv.second;

    std::vector<float> audio;
    float sample_rate;
    ReadAudio(audio_file, &audio, &sample_rate);

    feature_extractor.PushAudio(audio.data(), audio.size(), sample_rate);
    feature_extractor.EndOfAudio();
    EXPECT_EQ(num_frames, feature_extractor.NumFrames());

    kaldi::Vector<float> one_frame(feature_extractor.Dim());
    for (int f = 0; f < feature_extractor.NumFrames(); f++) {
      feature_extractor.GetFrame(f, &one_frame);
    }
    feature_extractor.Reset();
  }
}

} // namespace sio
