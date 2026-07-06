---
layout: end
transition: fade
hideInToc: true
---

# 谢谢各位老师

<div class="mt-6 text-xl text-slate-600">
  整个系统按四层架构组织，<code>core / graphics / canvas / ui</code> 边界固定，44 个文件、4431 行代码、5 个测试模块、40 个用例。各位老师如果有具体问题，欢迎在这一页停留。
</div>

<div class="mt-10 text-sm text-slate-400">
  <code>Vector Graphics Editor</code> · 面向对象程序设计课程设计
</div>

<!--
各位老师，演示到这里。整套系统的核心：四层架构边界固定，core 层不引 Qt Widgets，可以在没有 QApplication 的测试进程里跑。ShapeData 是跨层唯一边界对象，序列化、文件 I/O、复制粘贴都走它。运行时多态靠 ICreationStrategy，依赖注入靠 CreationContext，输入状态机互斥由 CanvasView 路由。40 个测试用例覆盖序列化、几何、命中、菜单分组三条回归线。质量门禁由 clang-format、clang-tidy、ctest 三件套组成。跨平台三套 preset。如果老师有问题，可以在这一页停留提问。
-->
