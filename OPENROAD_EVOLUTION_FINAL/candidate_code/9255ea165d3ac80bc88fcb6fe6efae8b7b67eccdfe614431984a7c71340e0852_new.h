// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95953730;
  double density_weight = 0.21472442;
  double prefix_weight = 0.34335702;
  double neighborhood_weight = 0.25002671;
  double late_weight = 0.12018615;
  double critical_weight = 0.40038371;
  unsigned budget = 36;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
