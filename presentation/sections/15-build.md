---
layout: default
transition: slide-left
---

# 国际化与主题

<div class="deck-rule"></div>

<div class="deck-lead">
  国际化与主题切换是完整桌面应用体验的一部分。系统把语言、主题和重启后状态恢复作为一个整体处理。
</div>

<div class="rail-list">
  <div v-click class="rail-item">
    <div class="rail-index">国际化</div>
    <div class="rail-title"><code>AppLanguage</code> + <code>I18n</code></div>
    <div class="rail-copy"><code>English / SimplifiedChinese</code> 两种语言。图形名、线型名、菜单文案统一走 <code>I18n</code> 接口。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">主题</div>
    <div class="rail-title"><code>ThemeMode</code> + Fusion 调色板</div>
    <div class="rail-copy"><code>System / Light / Dark</code> 三档，<code>applyApplicationTheme()</code> 统一应用。底层用 Qt Fusion 风格。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">状态恢复</div>
    <div class="rail-title">QSettings 持久化</div>
    <div class="rail-copy">语言和主题写入 <code>QSettings</code>，重启后保留。<code>System</code> 模式监听 <code>QStyleHints::colorSchemeChanged</code> 跟随系统。</div>
  </div>
</div>

<!--
各位老师，AppLanguage 枚举两种语言，ThemeMode 枚举三档。System 模式额外监听系统外观变化，这是和普通 Light / Dark 的关键差异。语言偏好和主题写入 QSettings 重启后保留。
-->
