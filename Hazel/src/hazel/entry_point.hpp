#ifdef HAZEL_PLATFORM_WINDOWS

extern hazel::Application* hazel::CreateApplication();

int main(int argc, char** argv) {
  std::cout << "new hazel entry point\n";
  auto app = hazel::CreateApplication();
  app->Run();
  delete app;
}

#endif