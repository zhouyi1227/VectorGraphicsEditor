---
layout: default
transition: slide-left
---

# 国际化与主题

<div class="deck-rule"></div>

<div class="deck-lead">
  国际化和主题切换不是装饰项。它们说明这个项目不仅关心“图能不能画对”，也关心用户每次启动、切换语言和适配系统外观时能否保持一致体验。
</div>

<div class="rail-list">
  <div v-click class="rail-item">
    <div class="rail-index">CAPABILITY</div>
    <div class="rail-title">国际化能力</div>
    <div class="rail-copy"><code>AppLanguage</code> 明确维护 <code>English / SimplifiedChinese</code> 两种状态；图形名、线型名、菜单文案和状态栏提示统一走 <code>I18n</code> 接口。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">IMPLEMENTATION</div>
    <div class="rail-title">主题实现方式</div>
    <div class="rail-copy"><code>ThemeMode</code> 提供 <code>System / Light / Dark</code> 三档，统一由 <code>applyApplicationTheme()</code> 应用；界面使用 <code>Fusion</code> 风格和自定义调色板保持一致。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">VALUE</div>
    <div class="rail-title">一致性与状态恢复</div>
    <div class="rail-copy">语言偏好和主题模式会写入 <code>QSettings</code>，<code>TutorialDialog</code> 中的双语 HTML 手册也会同步切换，说明系统把文案、外观和状态恢复作为一个整体处理。</div>
  </div>
</div>

<!--
国际化和主题不是“锦上添花”的功能。对课程项目来说，它们说明系统不是一堆功能堆砌，而是从状态持久化、文案组织到视觉一致性都经过了设计。
-->
