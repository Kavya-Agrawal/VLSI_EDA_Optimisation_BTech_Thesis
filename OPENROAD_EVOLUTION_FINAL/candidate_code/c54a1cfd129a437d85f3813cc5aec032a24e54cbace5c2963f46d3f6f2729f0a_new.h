// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44690103;
  double density_weight = 0.59983658;
  double prefix_weight = 0.02375847;
  double neighborhood_weight = 0.15016919;
  double late_weight = 0.10698152;
  double critical_weight = 0.11153947;
  unsigned budget = 28;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
