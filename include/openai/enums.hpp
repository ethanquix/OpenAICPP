#pragma once

namespace openai {
  enum AI_MODELS {
    GPT432K0314,
    GPT432K,
    GPT40314,
    GPT4,
    GPT3Dot5Turbo0301,
    GPT3Dot5Turbo,
    GPT3TextDavinci003,
    GPT3TextDavinci002,
    GPT3TextCurie001,
    GPT3TextBabbage001,
    GPT3TextAda001,
    GPT3TextDavinci001,
    GPT3DavinciInstructBeta,
    GPT3Davinci,
    GPT3CurieInstructBeta,
    GPT3Curie,
    GPT3Ada,
    GPT3Babbage,
  };

  enum AI_MODELS_EDITS {
    TextDavinciEdit001,
    CodeDavinciEdit001
  };

  enum AI_MODELS_MODERATIONS {
    TextModerationStable,
    TextModerationLatest,
  };

  enum CHAT_ROLES {
    system,
    user,
    assistant
  };

  enum IMAGE_SIZE {
    px_256_256,
    px_512_512,
    px_1024_1024,
  };

  enum IMAGE_RESPONSE_FORMAT {
    url,
    b64_json,
  };

  enum AUDIO_RESPONSE_FORMAT {
    json,
    text,
    srt,
    verbose_json,
    vtt
  };

  // functions
  const char *to_str(AI_MODELS num) {
    switch (num) {
      case GPT432K0314: return "gpt-4-32k-0314";
      case GPT432K: return "gpt-4-32k";
      case GPT40314: return "gpt-4-0314";
      case GPT4: return "gpt-4";
      case GPT3Dot5Turbo0301: return "gpt-3.5-turbo-0301";
      case GPT3Dot5Turbo: return "gpt-3.5-turbo";
      case GPT3TextDavinci003: return "text-davinci-003";
      case GPT3TextDavinci002: return "text-davinci-002";
      case GPT3TextCurie001: return "text-curie-001";
      case GPT3TextBabbage001: return "text-babbage-001";
      case GPT3TextAda001: return "text-ada-001";
      case GPT3TextDavinci001: return "text-davinci-001";
      case GPT3DavinciInstructBeta: return "davinci-instruct-beta";
      case GPT3Davinci: return "davinci";
      case GPT3CurieInstructBeta: return "curie-instruct-beta";
      case GPT3Curie: return "curie";
      case GPT3Ada: return "ada";
      case GPT3Babbage: return "babbage";
    }
  }

  const char *to_str(AI_MODELS_EDITS num) {
    switch (num) {
      case TextDavinciEdit001: return "text-davinci-edit-001";
      case CodeDavinciEdit001: return "code-davinci-edit-001";
    }
  }

  const char *to_str(AI_MODELS_MODERATIONS num) {
    switch (num) {
      case TextModerationStable: return "text-moderation-stable";
      case TextModerationLatest: return "text-moderation-latest";
    }
  }

  const char *to_str(CHAT_ROLES num) {
    switch (num) {
      case system: return "system";
      case user: return "user";
      case assistant: return "assistant";
    }
  }

  const char *to_str(IMAGE_SIZE num) {
    switch (num) {
      case px_256_256: return "256x256";
      case px_512_512: return "512x512";
      case px_1024_1024: return "1024x1024";
    }
  }

  const char *to_str(IMAGE_RESPONSE_FORMAT num) {
    switch (num) {
      case url: return "url";
      case b64_json: return "b64_json";
    }
  }

  const char *to_str(AUDIO_RESPONSE_FORMAT num) {
    switch (num) {
      case json: return "json";
      case text: return "text";
      case srt: return "srt";
      case verbose_json: return "verbose_json";
      case vtt: return "vtt";
    }
  }
}
