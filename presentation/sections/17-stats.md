---
layout: default
transition: slide-left
---

# 项目数据

<div style="height:2px;width:32px;background:#2d7ff9;margin:0.5rem 0 1.5rem 0;"></div>

<div style="display:grid;grid-template-columns:repeat(3,1fr);gap:1rem;text-align:center;">

<div>
<div style="font-size:2.5rem;font-weight:700;color:#2d7ff9;">49</div>
<div style="font-size:0.85rem;">源文件</div>
<div class="dim" style="font-size:0.7rem;">26 .cpp + 23 .h</div>
</div>

<div>
<div style="font-size:2.5rem;font-weight:700;color:#2d7ff9;">7</div>
<div style="font-size:0.85rem;">图形类型</div>
<div class="dim" style="font-size:0.7rem;">Point → Polygon</div>
</div>

<div>
<div style="font-size:2.5rem;font-weight:700;color:#2d7ff9;">5</div>
<div style="font-size:0.85rem;">enum class</div>
<div class="dim" style="font-size:0.7rem;">全部 :uint8_t</div>
</div>

<div>
<div style="font-size:2.5rem;font-weight:700;color:#2d7ff9;">25</div>
<div style="font-size:0.85rem;">override</div>
<div class="dim" style="font-size:0.7rem;">编译时签名校验</div>
</div>

<div>
<div style="font-size:2.5rem;font-weight:700;color:#2d7ff9;">40</div>
<div style="font-size:0.85rem;">测试用例</div>
<div class="dim" style="font-size:0.7rem;">5 测试模块</div>
</div>

<div>
<div style="font-size:2.5rem;font-weight:700;color:#2d7ff9;">6</div>
<div style="font-size:0.85rem;">CMake 预设</div>
<div class="dim" style="font-size:0.7rem;">三平台各 Debug/Release</div>
</div>

</div>

<div style="margin-top:2rem;text-align:center;font-size:0.85rem;color:#999;">
C++20 · Qt 6.8 · CMake ≥ 3.24 · Ninja
</div>

<!--
关键数据汇总：49个源文件11000行代码，7种图形类型，5个强类型枚举全部指定uint8_t底层类型节省内存，25个override关键字保证虚函数签名的编译时校验，40个测试用例分布在5个测试模块中验证核心逻辑和边界条件，6个CMake预设覆盖三平台各两种构建配置。
-->
