#ifdef HAZEL_PLATFORM_WINDOWS

extern hazel::Application* hazel::CreateApplication();

int main(int argc, char** argv) {
  hazel::Log::Init();

  auto app = hazel::CreateApplication();
  app->Run();
  delete app;
}

#endif