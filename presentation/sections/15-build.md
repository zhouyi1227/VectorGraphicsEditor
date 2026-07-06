---
layout: default
transition: slide-left
---

# 构建系统

<div style="height:2px;width:32px;background:#2d7ff9;margin:0.5rem 0 1.5rem 0;"></div>

<div class="dim" style="font-size:0.85rem;margin-bottom:1rem;">CMake ≥ 3.24 · Ninja · 三平台六配置</div>

<div style="display:grid;grid-template-columns:repeat(3,1fr);gap:0.75rem;margin-bottom:1.5rem;">

<div style="border:1px solid #e8e8e8;border-radius:4px;padding:0.8rem;">
<div style="font-weight:600;font-size:0.85rem;">Windows</div>
<div style="font-size:0.8rem;color:#666;">MSYS2 UCRT64</div>
<div class="dim" style="font-size:0.7rem;">GCC + Qt6</div>
</div>

<div style="border:1px solid #e8e8e8;border-radius:4px;padding:0.8rem;">
<div style="font-weight:600;font-size:0.85rem;">Linux</div>
<div style="font-size:0.8rem;color:#666;">system Qt6</div>
<div class="dim" style="font-size:0.7rem;">GCC / Clang</div>
</div>

<div style="border:1px solid #e8e8e8;border-radius:4px;padding:0.8rem;">
<div style="font-weight:600;font-size:0.85rem;">macOS</div>
<div style="font-size:0.8rem;color:#666;">Homebrew Qt6</div>
<div class="dim" style="font-size:0.7rem;">Apple Clang</div>
</div>

</div>

<div style="display:grid;grid-template-columns:1fr 1fr;gap:1rem;margin-bottom:1rem;">

<v-click>

<div style="background:#fafafa;border:1px solid #e8e8e8;border-radius:6px;padding:1rem;">

<div style="font-weight:600;font-size:0.85rem;margin-bottom:0.3rem;">编译警告</div>

```cmake
if(MSVC)
  target_compile_options(
    /W4 /permissive-
    /Zc:__cplusplus)
else()
  target_compile_options(
    -Wall -Wextra -Wpedantic)
endif()
```

</div>

</v-click>

<v-click>

<div style="background:#fafafa;border:1px solid #e8e8e8;border-radius:6px;padding:1rem;">

<div style="font-weight:600;font-size:0.85rem;margin-bottom:0.3rem;">clang-tidy</div>

```yaml
Checks: >
  bugprone-*,
  clang-analyzer-*,
  modernize-use-override,
  performance-*,
  readability-*
```

<div style="margin-top:0.5rem;font-size:0.85rem;">
<strong>clang-format</strong> — LLVM · 4 indent · 120 col
</div>

</div>

</v-click>

</div>

<v-click>

<div style="font-size:0.85rem;color:#666;text-align:center;">
CMake 目标: <code>svg_editor_core</code> (静态库) + <code>SVG_Editor</code> (可执行) · 自定义: format / format-check / lint / typecheck
</div>

</v-click>

<!--
构建系统使用CMake 3.24以上版本，Ninja生成器。预设覆盖三平台：Windows MSYS2 UCRT64，Linux系统Qt6，macOS Homebrew。编译警告严格：MSVC使用/W4和/permissive-，GCC/Clang使用-Wall -Wextra -Wpedantic。clang-tidy检查启用bugprone、analyzer、modernize、performance、readability等大类。项目构建两个CMake目标：svg_editor_core静态库只依赖Qt6::Core和Qt6::Gui，SVG_Editor可执行文件额外链接Widgets。
-->
